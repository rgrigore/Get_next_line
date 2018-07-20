/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrigore <rgrigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:07:23 by rgrigore          #+#    #+#             */
/*   Updated: 2018/01/11 11:07:25 by rgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define CONTENT tmp->content

/*
** function for selecting the right element from the list
*/

static t_list	*get_file(t_list **list, int fd)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(list, tmp);
	return (*list);
}

/*
** return function that also frees the memory
*/

static int		finish(char *tmp, int code)
{
	free(tmp);
	return (code);
}

/*
** the main function
*/

int				get_next_line(int fd, char **line)
{
	char			*buf;
	static t_list	*list;
	t_list			*tmp;
	int				ct;

	if (!(buf = ft_memalloc(BUFF_SIZE + 1)))
		return (-1);
	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (finish(buf, -1));
	tmp = get_file(&list, fd);
	if (!(*line = ft_strnew(1)))
		return (finish(buf, -1));
	while (!ft_strchr(buf, '\n') && (ct = read(fd, buf, BUFF_SIZE)))
	{
		buf[ct] = '\0';
		if (!(CONTENT = ft_strjoin(CONTENT, buf)))
			return (finish(buf, -1));
	}
	if (ct < BUFF_SIZE && !ft_strlen(CONTENT))
		return (finish(buf, 0));
	((ct = ft_strchrcpy(line, CONTENT, '\n')) < (int)ft_strlen(CONTENT)) ?
		CONTENT += (ct + 1)
		: ft_strclr(CONTENT);
	return (finish(buf, 1));
}

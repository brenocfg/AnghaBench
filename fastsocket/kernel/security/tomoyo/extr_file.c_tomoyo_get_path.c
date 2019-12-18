#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tomoyo_path_info {int /*<<< orphan*/  name; } ;
struct tomoyo_path_info_with_data {struct tomoyo_path_info head; int /*<<< orphan*/  body; } ;
struct path {int dummy; } ;

/* Variables and functions */
 struct tomoyo_path_info_with_data* tomoyo_alloc (int) ; 
 int /*<<< orphan*/  tomoyo_fill_path_info (struct tomoyo_path_info*) ; 
 int /*<<< orphan*/  tomoyo_free (struct tomoyo_path_info_with_data*) ; 
 int tomoyo_realpath_from_path2 (struct path*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct tomoyo_path_info *tomoyo_get_path(struct path *path)
{
	int error;
	struct tomoyo_path_info_with_data *buf = tomoyo_alloc(sizeof(*buf));

	if (!buf)
		return NULL;
	/* Reserve one byte for appending "/". */
	error = tomoyo_realpath_from_path2(path, buf->body,
					   sizeof(buf->body) - 2);
	if (!error) {
		buf->head.name = buf->body;
		tomoyo_fill_path_info(&buf->head);
		return &buf->head;
	}
	tomoyo_free(buf);
	return NULL;
}
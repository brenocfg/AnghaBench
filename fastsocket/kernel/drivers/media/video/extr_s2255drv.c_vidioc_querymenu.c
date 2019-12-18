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
struct v4l2_querymenu {scalar_t__ id; int index; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CID_PRIVATE_COLORFILTER ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int v4l2_ctrl_query_menu (struct v4l2_querymenu*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_querymenu(struct file *file, void *priv,
			    struct v4l2_querymenu *qmenu)
{
	static const char *colorfilter[] = {
		"Off",
		"On",
		NULL
	};
	if (qmenu->id == V4L2_CID_PRIVATE_COLORFILTER) {
		int i;
		const char **menu_items = colorfilter;
		for (i = 0; i < qmenu->index && menu_items[i]; i++)
			; /* do nothing (from v4l2-common.c) */
		if (menu_items[i] == NULL || menu_items[i][0] == '\0')
			return -EINVAL;
		strlcpy(qmenu->name, menu_items[qmenu->index],
			sizeof(qmenu->name));
		return 0;
	}
	return v4l2_ctrl_query_menu(qmenu, NULL, NULL);
}
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
struct v4l2_querymenu {int index; int /*<<< orphan*/  name; int /*<<< orphan*/  id; scalar_t__ reserved; } ;
struct v4l2_queryctrl {int minimum; int maximum; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const* const,int) ; 
 char** v4l2_ctrl_get_menu (int /*<<< orphan*/ ) ; 

int v4l2_ctrl_query_menu(struct v4l2_querymenu *qmenu, struct v4l2_queryctrl *qctrl,
	       const char * const *menu_items)
{
	int i;

	qmenu->reserved = 0;
	if (menu_items == NULL)
		menu_items = v4l2_ctrl_get_menu(qmenu->id);
	if (menu_items == NULL ||
	    (qctrl && (qmenu->index < qctrl->minimum || qmenu->index > qctrl->maximum)))
		return -EINVAL;
	for (i = 0; i < qmenu->index && menu_items[i]; i++) ;
	if (menu_items[i] == NULL || menu_items[i][0] == '\0')
		return -EINVAL;
	strlcpy(qmenu->name, menu_items[qmenu->index], sizeof(qmenu->name));
	return 0;
}
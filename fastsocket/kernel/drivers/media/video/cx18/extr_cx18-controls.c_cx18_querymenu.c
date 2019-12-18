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
struct v4l2_querymenu {int /*<<< orphan*/  id; } ;
struct v4l2_queryctrl {int /*<<< orphan*/  id; } ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx18_queryctrl (struct file*,void*,struct v4l2_queryctrl*) ; 
 int /*<<< orphan*/  cx2341x_ctrl_get_menu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_query_menu (struct v4l2_querymenu*,struct v4l2_queryctrl*,int /*<<< orphan*/ ) ; 

int cx18_querymenu(struct file *file, void *fh, struct v4l2_querymenu *qmenu)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;
	struct v4l2_queryctrl qctrl;

	qctrl.id = qmenu->id;
	cx18_queryctrl(file, fh, &qctrl);
	return v4l2_ctrl_query_menu(qmenu, &qctrl,
			cx2341x_ctrl_get_menu(&cx->params, qmenu->id));
}
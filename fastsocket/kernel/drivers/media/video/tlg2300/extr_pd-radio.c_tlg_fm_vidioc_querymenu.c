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
struct v4l2_querymenu {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int v4l2_ctrl_query_menu (struct v4l2_querymenu*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tlg_fm_vidioc_querymenu(struct file *file, void *fh,
				struct v4l2_querymenu *qmenu)
{
	return v4l2_ctrl_query_menu(qmenu, NULL, NULL);
}
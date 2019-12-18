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
struct cx8802_fh {struct cx8802_dev* dev; } ;
struct cx8802_dev {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  blackbird_queryctrl (struct cx8802_dev*,struct v4l2_queryctrl*) ; 
 int /*<<< orphan*/  cx2341x_ctrl_get_menu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_query_menu (struct v4l2_querymenu*,struct v4l2_queryctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_querymenu (struct file *file, void *priv,
				struct v4l2_querymenu *qmenu)
{
	struct cx8802_dev *dev  = ((struct cx8802_fh *)priv)->dev;
	struct v4l2_queryctrl qctrl;

	qctrl.id = qmenu->id;
	blackbird_queryctrl(dev, &qctrl);
	return v4l2_ctrl_query_menu(qmenu, &qctrl,
			cx2341x_ctrl_get_menu(&dev->params, qmenu->id));
}
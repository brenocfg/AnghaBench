#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_querymenu {int dummy; } ;
struct gspca_dev {TYPE_1__* sd_desc; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* querymenu ) (struct gspca_dev*,struct v4l2_querymenu*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct gspca_dev*,struct v4l2_querymenu*) ; 

__attribute__((used)) static int vidioc_querymenu(struct file *file, void *priv,
			    struct v4l2_querymenu *qmenu)
{
	struct gspca_dev *gspca_dev = priv;

	if (!gspca_dev->sd_desc->querymenu)
		return -EINVAL;
	return gspca_dev->sd_desc->querymenu(gspca_dev, qmenu);
}
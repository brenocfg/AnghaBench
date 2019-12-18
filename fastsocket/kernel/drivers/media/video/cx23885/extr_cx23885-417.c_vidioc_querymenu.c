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
struct cx23885_fh {struct cx23885_dev* dev; } ;
struct cx23885_dev {int dummy; } ;

/* Variables and functions */
 int cx23885_querymenu (struct cx23885_dev*,struct v4l2_querymenu*) ; 

__attribute__((used)) static int vidioc_querymenu(struct file *file, void *priv,
				struct v4l2_querymenu *a)
{
	struct cx23885_fh  *fh  = priv;
	struct cx23885_dev *dev = fh->dev;

	return cx23885_querymenu(dev, a);
}
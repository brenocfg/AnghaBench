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
struct vivi_fh {struct vivi_dev* dev; } ;
struct vivi_dev {unsigned int input; } ;
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int vidioc_g_input(struct file *file, void *priv, unsigned int *i)
{
	struct vivi_fh *fh = priv;
	struct vivi_dev *dev = fh->dev;

	*i = dev->input;

	return (0);
}
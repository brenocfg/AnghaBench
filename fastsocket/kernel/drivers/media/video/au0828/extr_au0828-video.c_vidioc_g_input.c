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
struct file {int dummy; } ;
struct au0828_fh {struct au0828_dev* dev; } ;
struct au0828_dev {unsigned int ctrl_input; } ;

/* Variables and functions */

__attribute__((used)) static int vidioc_g_input(struct file *file, void *priv, unsigned int *i)
{
	struct au0828_fh *fh = priv;
	struct au0828_dev *dev = fh->dev;
	*i = dev->ctrl_input;
	return 0;
}
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
struct saa7134_fh {struct saa7134_dev* dev; } ;
struct saa7134_dev {unsigned int ctl_input; } ;
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int saa7134_g_input(struct file *file, void *priv, unsigned int *i)
{
	struct saa7134_fh *fh = priv;
	struct saa7134_dev *dev = fh->dev;

	*i = dev->ctl_input;
	return 0;
}
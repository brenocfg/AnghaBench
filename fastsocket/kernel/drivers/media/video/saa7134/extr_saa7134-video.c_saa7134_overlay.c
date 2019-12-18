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
struct saa7134_dev {int /*<<< orphan*/  slock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  res_check (struct saa7134_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_free (struct saa7134_dev*,struct saa7134_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_get (struct saa7134_dev*,struct saa7134_fh*,int /*<<< orphan*/ ) ; 
 scalar_t__ saa7134_no_overlay ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_preview (struct saa7134_dev*,struct saa7134_fh*) ; 
 int /*<<< orphan*/  stop_preview (struct saa7134_dev*,struct saa7134_fh*) ; 

__attribute__((used)) static int saa7134_overlay(struct file *file, void *f, unsigned int on)
{
	struct saa7134_fh *fh = f;
	struct saa7134_dev *dev = fh->dev;
	unsigned long flags;

	if (on) {
		if (saa7134_no_overlay > 0) {
			dprintk("no_overlay\n");
			return -EINVAL;
		}

		if (!res_get(dev, fh, RESOURCE_OVERLAY))
			return -EBUSY;
		spin_lock_irqsave(&dev->slock, flags);
		start_preview(dev, fh);
		spin_unlock_irqrestore(&dev->slock, flags);
	}
	if (!on) {
		if (!res_check(fh, RESOURCE_OVERLAY))
			return -EINVAL;
		spin_lock_irqsave(&dev->slock, flags);
		stop_preview(dev, fh);
		spin_unlock_irqrestore(&dev->slock, flags);
		res_free(dev, fh, RESOURCE_OVERLAY);
	}
	return 0;
}
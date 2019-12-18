#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct saa7134_fh {int /*<<< orphan*/  prio; } ;
struct saa7134_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  slock; int /*<<< orphan*/  prio; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 unsigned int TVNORMS ; 
 int V4L2_STD_SECAM ; 
 int V4L2_STD_SECAM_DK ; 
 int V4L2_STD_SECAM_L ; 
 int V4L2_STD_SECAM_LC ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ res_check (struct saa7134_fh*,int /*<<< orphan*/ ) ; 
 scalar_t__ res_locked (struct saa7134_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7134_tvaudio_do_scan (struct saa7134_dev*) ; 
 char* secam ; 
 int /*<<< orphan*/  set_tvnorm (struct saa7134_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_preview (struct saa7134_dev*,struct saa7134_fh*) ; 
 int /*<<< orphan*/  stop_preview (struct saa7134_dev*,struct saa7134_fh*) ; 
 TYPE_1__* tvnorms ; 
 int v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int saa7134_s_std_internal(struct saa7134_dev *dev, struct saa7134_fh *fh, v4l2_std_id *id)
{
	unsigned long flags;
	unsigned int i;
	v4l2_std_id fixup;
	int err;

	/* When called from the empress code fh == NULL.
	   That needs to be fixed somehow, but for now this is
	   good enough. */
	if (fh) {
		err = v4l2_prio_check(&dev->prio, fh->prio);
		if (0 != err)
			return err;
	} else if (res_locked(dev, RESOURCE_OVERLAY)) {
		/* Don't change the std from the mpeg device
		   if overlay is active. */
		return -EBUSY;
	}

	for (i = 0; i < TVNORMS; i++)
		if (*id == tvnorms[i].id)
			break;

	if (i == TVNORMS)
		for (i = 0; i < TVNORMS; i++)
			if (*id & tvnorms[i].id)
				break;
	if (i == TVNORMS)
		return -EINVAL;

	if ((*id & V4L2_STD_SECAM) && (secam[0] != '-')) {
		if (secam[0] == 'L' || secam[0] == 'l') {
			if (secam[1] == 'C' || secam[1] == 'c')
				fixup = V4L2_STD_SECAM_LC;
			else
				fixup = V4L2_STD_SECAM_L;
		} else {
			if (secam[0] == 'D' || secam[0] == 'd')
				fixup = V4L2_STD_SECAM_DK;
			else
				fixup = V4L2_STD_SECAM;
		}
		for (i = 0; i < TVNORMS; i++) {
			if (fixup == tvnorms[i].id)
				break;
		}
		if (i == TVNORMS)
			return -EINVAL;
	}

	*id = tvnorms[i].id;

	mutex_lock(&dev->lock);
	if (fh && res_check(fh, RESOURCE_OVERLAY)) {
		spin_lock_irqsave(&dev->slock, flags);
		stop_preview(dev, fh);
		spin_unlock_irqrestore(&dev->slock, flags);

		set_tvnorm(dev, &tvnorms[i]);

		spin_lock_irqsave(&dev->slock, flags);
		start_preview(dev, fh);
		spin_unlock_irqrestore(&dev->slock, flags);
	} else
		set_tvnorm(dev, &tvnorms[i]);

	saa7134_tvaudio_do_scan(dev);
	mutex_unlock(&dev->lock);
	return 0;
}
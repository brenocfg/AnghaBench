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
struct saa7134_fh {int /*<<< orphan*/  prio; struct saa7134_dev* dev; } ;
struct saa7134_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  prio; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SAA7134_INPUT_MAX ; 
 TYPE_1__ card_in (struct saa7134_dev*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_mux (struct saa7134_dev*,unsigned int) ; 

__attribute__((used)) static int saa7134_s_input(struct file *file, void *priv, unsigned int i)
{
	struct saa7134_fh *fh = priv;
	struct saa7134_dev *dev = fh->dev;
	int err;

	err = v4l2_prio_check(&dev->prio, fh->prio);
	if (0 != err)
		return err;

	if (i >= SAA7134_INPUT_MAX)
		return -EINVAL;
	if (NULL == card_in(dev, i).name)
		return -EINVAL;
	mutex_lock(&dev->lock);
	video_mux(dev, i);
	mutex_unlock(&dev->lock);
	return 0;
}
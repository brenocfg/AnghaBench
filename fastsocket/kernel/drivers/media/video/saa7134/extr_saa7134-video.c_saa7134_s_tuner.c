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
struct v4l2_tuner {int audmode; int /*<<< orphan*/  rxsubchans; } ;
struct saa7134_fh {int /*<<< orphan*/  prio; struct saa7134_dev* dev; } ;
struct TYPE_2__ {int mode; } ;
struct saa7134_dev {TYPE_1__ thread; int /*<<< orphan*/  prio; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int UNSET ; 
 int saa7134_tvaudio_getstereo (struct saa7134_dev*) ; 
 int saa7134_tvaudio_rx2mode (int /*<<< orphan*/ ) ; 
 int v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa7134_s_tuner(struct file *file, void *priv,
					struct v4l2_tuner *t)
{
	struct saa7134_fh *fh = priv;
	struct saa7134_dev *dev = fh->dev;
	int rx, mode, err;

	err = v4l2_prio_check(&dev->prio, fh->prio);
	if (0 != err)
		return err;

	mode = dev->thread.mode;
	if (UNSET == mode) {
		rx   = saa7134_tvaudio_getstereo(dev);
		mode = saa7134_tvaudio_rx2mode(t->rxsubchans);
	}
	if (mode != t->audmode)
		dev->thread.mode = t->audmode;

	return 0;
}
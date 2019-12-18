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
struct v4l2_tuner {int /*<<< orphan*/  audmode; scalar_t__ index; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct mxb {int /*<<< orphan*/  cur_mode; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int EINVAL ; 
 int call_all (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 int /*<<< orphan*/  s_tuner ; 
 int /*<<< orphan*/  tuner ; 

__attribute__((used)) static int vidioc_s_tuner(struct file *file, void *fh, struct v4l2_tuner *t)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct mxb *mxb = (struct mxb *)dev->ext_priv;

	if (t->index) {
		DEB_D(("VIDIOC_S_TUNER: channel %d does not have a tuner attached.\n", t->index));
		return -EINVAL;
	}

	mxb->cur_mode = t->audmode;
	return call_all(dev, tuner, s_tuner, t);
}
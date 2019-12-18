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
struct v4l2_frequency {scalar_t__ type; int /*<<< orphan*/  frequency; scalar_t__ tuner; } ;
struct saa7146_vv {scalar_t__ vbi_fieldcount; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {int /*<<< orphan*/  slock; struct saa7146_vv* vv_data; scalar_t__ ext_priv; } ;
struct mxb {struct v4l2_frequency cur_freq; scalar_t__ cur_input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  tuner_call (struct mxb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *fh, struct v4l2_frequency *f)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct mxb *mxb = (struct mxb *)dev->ext_priv;
	struct saa7146_vv *vv = dev->vv_data;

	if (f->tuner)
		return -EINVAL;

	if (V4L2_TUNER_ANALOG_TV != f->type)
		return -EINVAL;

	if (mxb->cur_input) {
		DEB_D(("VIDIOC_S_FREQ: channel %d does not have a tuner!\n", mxb->cur_input));
		return -EINVAL;
	}

	mxb->cur_freq = *f;
	DEB_EE(("VIDIOC_S_FREQUENCY: freq:0x%08x.\n", mxb->cur_freq.frequency));

	/* tune in desired frequency */
	tuner_call(mxb, tuner, s_frequency, &mxb->cur_freq);

	/* hack: changing the frequency should invalidate the vbi-counter (=> alevt) */
	spin_lock(&dev->slock);
	vv->vbi_fieldcount = 0;
	spin_unlock(&dev->slock);

	return 0;
}
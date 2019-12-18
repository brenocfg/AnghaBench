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
struct v4l2_audio {scalar_t__ index; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct mxb {size_t cur_input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int EINVAL ; 
 scalar_t__ MXB_INPUTS ; 
 int /*<<< orphan*/  memcpy (struct v4l2_audio*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mxb_audios ; 
 size_t* video_audio_connect ; 

__attribute__((used)) static int vidioc_g_audio(struct file *file, void *fh, struct v4l2_audio *a)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct mxb *mxb = (struct mxb *)dev->ext_priv;

	if (a->index > MXB_INPUTS) {
		DEB_D(("VIDIOC_G_AUDIO %d out of range.\n", a->index));
		return -EINVAL;
	}

	DEB_EE(("VIDIOC_G_AUDIO %d.\n", a->index));
	memcpy(a, &mxb_audios[video_audio_connect[mxb->cur_input]], sizeof(struct v4l2_audio));
	return 0;
}
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
typedef  scalar_t__ u16 ;
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct maestro {int /*<<< orphan*/  lock; int /*<<< orphan*/  muted; scalar_t__ io; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IO_MASK ; 
 scalar_t__ STR_WREN ; 
#define  V4L2_CID_AUDIO_MUTE 128 
 scalar_t__ inw (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 struct maestro* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *priv,
					struct v4l2_control *ctrl)
{
	struct maestro *dev = video_drvdata(file);
	u16 io = dev->io;
	u16 omask;

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		mutex_lock(&dev->lock);
		omask = inw(io + IO_MASK);
		outw(~STR_WREN, io + IO_MASK);
		dev->muted = ctrl->value;
		outw(dev->muted ? STR_WREN : 0, io);
		udelay(4);
		outw(omask, io + IO_MASK);
		msleep(125);
		mutex_unlock(&dev->lock);
		return 0;
	}
	return -EINVAL;
}
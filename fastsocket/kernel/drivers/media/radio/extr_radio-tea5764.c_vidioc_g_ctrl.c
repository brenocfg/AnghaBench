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
struct v4l2_control {int id; int value; } ;
struct tea5764_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_MUTE 128 
 int /*<<< orphan*/  tea5764_i2c_read (struct tea5764_device*) ; 
 int /*<<< orphan*/  tea5764_is_muted (struct tea5764_device*) ; 
 struct tea5764_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_ctrl(struct file *file, void *priv,
			    struct v4l2_control *ctrl)
{
	struct tea5764_device *radio = video_drvdata(file);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		tea5764_i2c_read(radio);
		ctrl->value = tea5764_is_muted(radio) ? 1 : 0;
		return 0;
	}
	return -EINVAL;
}
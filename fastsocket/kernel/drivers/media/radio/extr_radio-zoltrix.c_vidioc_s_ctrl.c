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
struct zoltrix {int curvol; int stereo; int /*<<< orphan*/  curfreq; } ;
struct v4l2_control {int id; int value; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_MUTE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int VIDEO_SOUND_MONO ; 
 int VIDEO_SOUND_STEREO ; 
 TYPE_1__* v ; 
 struct zoltrix* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  zol_mute (struct zoltrix*) ; 
 scalar_t__ zol_setfreq (struct zoltrix*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zol_setvol (struct zoltrix*,int) ; 
 int /*<<< orphan*/  zol_unmute (struct zoltrix*) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *priv,
				struct v4l2_control *ctrl)
{
	struct zoltrix *zol = video_drvdata(file);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		if (ctrl->value)
			zol_mute(zol);
		else {
			zol_unmute(zol);
			zol_setvol(zol, zol->curvol);
		}
		return 0;
	case V4L2_CID_AUDIO_VOLUME:
		zol_setvol(zol, ctrl->value / 4096);
		return 0;
	}
	zol->stereo = 1;
	if (zol_setfreq(zol, zol->curfreq) != 0)
		return -EINVAL;
#if 0
/* FIXME: Implement stereo/mono switch on V4L2 */
	if (v->mode & VIDEO_SOUND_STEREO) {
		zol->stereo = 1;
		zol_setfreq(zol, zol->curfreq);
	}
	if (v->mode & VIDEO_SOUND_MONO) {
		zol->stereo = 0;
		zol_setfreq(zol, zol->curfreq);
	}
#endif
	return -EINVAL;
}
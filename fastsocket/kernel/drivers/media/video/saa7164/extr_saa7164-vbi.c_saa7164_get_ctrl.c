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
struct v4l2_ext_control {int id; int /*<<< orphan*/  value; } ;
struct saa7164_vbi_params {int /*<<< orphan*/  gop_size; int /*<<< orphan*/  refdist; int /*<<< orphan*/  ctl_aspect; int /*<<< orphan*/  ctl_mute; int /*<<< orphan*/  stream_type; } ;
struct saa7164_port {struct saa7164_vbi_params vbi_params; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_MPEG_AUDIO_MUTE 132 
#define  V4L2_CID_MPEG_STREAM_TYPE 131 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 130 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 129 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 128 

__attribute__((used)) static int saa7164_get_ctrl(struct saa7164_port *port,
	struct v4l2_ext_control *ctrl)
{
	struct saa7164_vbi_params *params = &port->vbi_params;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_STREAM_TYPE:
		ctrl->value = params->stream_type;
		break;
	case V4L2_CID_MPEG_AUDIO_MUTE:
		ctrl->value = params->ctl_mute;
		break;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		ctrl->value = params->ctl_aspect;
		break;
	case V4L2_CID_MPEG_VIDEO_B_FRAMES:
		ctrl->value = params->refdist;
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		ctrl->value = params->gop_size;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
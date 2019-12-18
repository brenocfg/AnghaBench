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
struct saa7164_encoder_params {int /*<<< orphan*/  gop_size; int /*<<< orphan*/  bitrate_peak; int /*<<< orphan*/  refdist; int /*<<< orphan*/  bitrate_mode; int /*<<< orphan*/  ctl_aspect; int /*<<< orphan*/  ctl_mute; int /*<<< orphan*/  stream_type; int /*<<< orphan*/  bitrate; } ;
struct saa7164_port {struct saa7164_encoder_params encoder_params; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_MPEG_AUDIO_MUTE 135 
#define  V4L2_CID_MPEG_STREAM_TYPE 134 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 133 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 132 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 131 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 130 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 129 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 128 

__attribute__((used)) static int saa7164_get_ctrl(struct saa7164_port *port,
	struct v4l2_ext_control *ctrl)
{
	struct saa7164_encoder_params *params = &port->encoder_params;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		ctrl->value = params->bitrate;
		break;
	case V4L2_CID_MPEG_STREAM_TYPE:
		ctrl->value = params->stream_type;
		break;
	case V4L2_CID_MPEG_AUDIO_MUTE:
		ctrl->value = params->ctl_mute;
		break;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		ctrl->value = params->ctl_aspect;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		ctrl->value = params->bitrate_mode;
		break;
	case V4L2_CID_MPEG_VIDEO_B_FRAMES:
		ctrl->value = params->refdist;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		ctrl->value = params->bitrate_peak;
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		ctrl->value = params->gop_size;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
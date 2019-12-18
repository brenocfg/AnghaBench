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
typedef  void* uint ;
struct v4l2_ext_control {int id; int value; } ;
struct hdpvr_options {int audio_codec; void* bitrate; void* peak_bitrate; int /*<<< orphan*/  bitrate_mode; int /*<<< orphan*/  audio_input; } ;
struct hdpvr_device {int flags; struct hdpvr_options options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_BITRATE_MODE_VALUE ; 
 int EINVAL ; 
 int /*<<< orphan*/  HDPVR_CONSTANT ; 
 int HDPVR_FLAG_AC3_CAP ; 
 int /*<<< orphan*/  HDPVR_VARIABLE_AVERAGE ; 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 133 
#define  V4L2_CID_MPEG_STREAM_TYPE 132 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 131 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 130 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 129 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 128 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int /*<<< orphan*/  hdpvr_config_call (struct hdpvr_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hdpvr_set_audio (struct hdpvr_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdpvr_set_bitrate (struct hdpvr_device*) ; 

__attribute__((used)) static int hdpvr_set_ctrl(struct hdpvr_device *dev,
			  struct v4l2_ext_control *ctrl)
{
	struct hdpvr_options *opt = &dev->options;
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		if (dev->flags & HDPVR_FLAG_AC3_CAP) {
			opt->audio_codec = ctrl->value;
			ret = hdpvr_set_audio(dev, opt->audio_input,
					      opt->audio_codec);
		}
		break;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		break;
/* 	case V4L2_CID_MPEG_VIDEO_B_FRAMES: */
/* 		if (ctrl->value == 0 && !(opt->gop_mode & 0x2)) { */
/* 			opt->gop_mode |= 0x2; */
/* 			hdpvr_config_call(dev, CTRL_GOP_MODE_VALUE, */
/* 					  opt->gop_mode); */
/* 		} */
/* 		if (ctrl->value == 128 && opt->gop_mode & 0x2) { */
/* 			opt->gop_mode &= ~0x2; */
/* 			hdpvr_config_call(dev, CTRL_GOP_MODE_VALUE, */
/* 					  opt->gop_mode); */
/* 		} */
/* 		break; */
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		if (ctrl->value == V4L2_MPEG_VIDEO_BITRATE_MODE_CBR &&
		    opt->bitrate_mode != HDPVR_CONSTANT) {
			opt->bitrate_mode = HDPVR_CONSTANT;
			hdpvr_config_call(dev, CTRL_BITRATE_MODE_VALUE,
					  opt->bitrate_mode);
		}
		if (ctrl->value == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR &&
		    opt->bitrate_mode == HDPVR_CONSTANT) {
			opt->bitrate_mode = HDPVR_VARIABLE_AVERAGE;
			hdpvr_config_call(dev, CTRL_BITRATE_MODE_VALUE,
					  opt->bitrate_mode);
		}
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE: {
		uint bitrate = ctrl->value / 100000;

		opt->bitrate = bitrate;
		if (bitrate >= opt->peak_bitrate)
			opt->peak_bitrate = bitrate+1;

		hdpvr_set_bitrate(dev);
		break;
	}
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK: {
		uint peak_bitrate = ctrl->value / 100000;

		if (opt->bitrate_mode == HDPVR_CONSTANT)
			break;

		if (opt->bitrate < peak_bitrate) {
			opt->peak_bitrate = peak_bitrate;
			hdpvr_set_bitrate(dev);
		} else
			ret = -EINVAL;
		break;
	}
	case V4L2_CID_MPEG_STREAM_TYPE:
		break;
	default:
		return -EINVAL;
	}
	return ret;
}
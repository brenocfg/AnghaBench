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
struct v4l2_tuner {int index; int capability; int rangelow; int rangehigh; int rxsubchans; int /*<<< orphan*/  signal; void* audmode; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct cadet {int /*<<< orphan*/  sigstrength; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_RDS ; 
 int V4L2_TUNER_CAP_STEREO ; 
 void* V4L2_TUNER_MODE_MONO ; 
 void* V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
#define  V4L2_TUNER_SUB_MONO 129 
 int V4L2_TUNER_SUB_RDS ; 
#define  V4L2_TUNER_SUB_STEREO 128 
 int cadet_getstereo (struct cadet*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct cadet* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_tuner(struct file *file, void *priv,
				struct v4l2_tuner *v)
{
	struct cadet *dev = video_drvdata(file);

	v->type = V4L2_TUNER_RADIO;
	switch (v->index) {
	case 0:
		strlcpy(v->name, "FM", sizeof(v->name));
		v->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_RDS;
		v->rangelow = 1400;     /* 87.5 MHz */
		v->rangehigh = 1728;    /* 108.0 MHz */
		v->rxsubchans = cadet_getstereo(dev);
		switch (v->rxsubchans) {
		case V4L2_TUNER_SUB_MONO:
			v->audmode = V4L2_TUNER_MODE_MONO;
			break;
		case V4L2_TUNER_SUB_STEREO:
			v->audmode = V4L2_TUNER_MODE_STEREO;
			break;
		default:
			break;
		}
		v->rxsubchans |= V4L2_TUNER_SUB_RDS;
		break;
	case 1:
		strlcpy(v->name, "AM", sizeof(v->name));
		v->capability = V4L2_TUNER_CAP_LOW;
		v->rangelow = 8320;      /* 520 kHz */
		v->rangehigh = 26400;    /* 1650 kHz */
		v->rxsubchans = V4L2_TUNER_SUB_MONO;
		v->audmode = V4L2_TUNER_MODE_MONO;
		break;
	default:
		return -EINVAL;
	}
	v->signal = dev->sigstrength; /* We might need to modify scaling of this */
	return 0;
}
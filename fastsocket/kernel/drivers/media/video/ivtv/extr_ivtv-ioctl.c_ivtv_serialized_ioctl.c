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
struct video_device {int debug; } ;
struct ivtv_open_id {int /*<<< orphan*/  prio; } ;
struct ivtv {int /*<<< orphan*/  prio; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int IVTV_DBGFLG_IOCTL ; 
 int V4L2_DEBUG_IOCTL ; 
 int V4L2_DEBUG_IOCTL_ARG ; 
#define  VIDIOC_OVERLAY 141 
#define  VIDIOC_S_AUDIO 140 
#define  VIDIOC_S_AUDOUT 139 
#define  VIDIOC_S_CROP 138 
#define  VIDIOC_S_CTRL 137 
#define  VIDIOC_S_EXT_CTRLS 136 
#define  VIDIOC_S_FBUF 135 
#define  VIDIOC_S_FMT 134 
#define  VIDIOC_S_FREQUENCY 133 
#define  VIDIOC_S_INPUT 132 
#define  VIDIOC_S_OUTPUT 131 
#define  VIDIOC_S_PRIORITY 130 
#define  VIDIOC_S_STD 129 
#define  VIDIOC_S_TUNER 128 
 struct ivtv_open_id* fh2id (int /*<<< orphan*/ ) ; 
 int ivtv_debug ; 
 long v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 
 long video_ioctl2 (struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long ivtv_serialized_ioctl(struct ivtv *itv, struct file *filp,
		unsigned int cmd, unsigned long arg)
{
	struct video_device *vfd = video_devdata(filp);
	struct ivtv_open_id *id = fh2id(filp->private_data);
	long ret;

	/* check priority */
	switch (cmd) {
	case VIDIOC_S_CTRL:
	case VIDIOC_S_STD:
	case VIDIOC_S_INPUT:
	case VIDIOC_S_OUTPUT:
	case VIDIOC_S_TUNER:
	case VIDIOC_S_FREQUENCY:
	case VIDIOC_S_FMT:
	case VIDIOC_S_CROP:
	case VIDIOC_S_AUDIO:
	case VIDIOC_S_AUDOUT:
	case VIDIOC_S_EXT_CTRLS:
	case VIDIOC_S_FBUF:
	case VIDIOC_S_PRIORITY:
	case VIDIOC_OVERLAY:
		ret = v4l2_prio_check(&itv->prio, id->prio);
		if (ret)
			return ret;
	}

	if (ivtv_debug & IVTV_DBGFLG_IOCTL)
		vfd->debug = V4L2_DEBUG_IOCTL | V4L2_DEBUG_IOCTL_ARG;
	ret = video_ioctl2(filp, cmd, arg);
	vfd->debug = 0;
	return ret;
}
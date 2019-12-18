#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_window {int dummy; } ;
struct video_picture {int dummy; } ;
struct file {struct cpia2_fh* private_data; } ;
struct cpia2_fh {int prio; } ;
struct TYPE_3__ {int /*<<< orphan*/  stream_mode; } ;
struct TYPE_4__ {TYPE_1__ camera_state; } ;
struct camera_data {int /*<<< orphan*/  busy_lock; int /*<<< orphan*/  streaming; int /*<<< orphan*/  mmapped; TYPE_2__ params; int /*<<< orphan*/  prio; int /*<<< orphan*/  vw; int /*<<< orphan*/  vp; int /*<<< orphan*/  present; } ;
typedef  enum v4l2_priority { ____Placeholder_v4l2_priority } v4l2_priority ;

/* Variables and functions */
#define  CPIA2_IOC_SET_GPIO 197 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 long EBUSY ; 
 long EINVAL ; 
 long ENODEV ; 
 long ENOIOCTLCMD ; 
 long ENOTTY ; 
 long ERESTARTSYS ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_PRIORITY_RECORD ; 
#define  VIDIOCCAPTURE 196 
#define  VIDIOCGAUDIO 195 
#define  VIDIOCGCAP 194 
#define  VIDIOCGCHAN 193 
#define  VIDIOCGFBUF 192 
#define  VIDIOCGFREQ 191 
#define  VIDIOCGMBUF 190 
#define  VIDIOCGPICT 189 
#define  VIDIOCGTUNER 188 
#define  VIDIOCGWIN 187 
#define  VIDIOCKEY 186 
#define  VIDIOCMCAPTURE 185 
#define  VIDIOCSAUDIO 184 
#define  VIDIOCSCHAN 183 
#define  VIDIOCSFBUF 182 
#define  VIDIOCSFREQ 181 
#define  VIDIOCSPICT 180 
#define  VIDIOCSTUNER 179 
#define  VIDIOCSWIN 178 
#define  VIDIOCSYNC 177 
#define  VIDIOC_CROPCAP 176 
#define  VIDIOC_DQBUF 175 
#define  VIDIOC_ENUMAUDIO 174 
#define  VIDIOC_ENUMAUDOUT 173 
#define  VIDIOC_ENUMINPUT 172 
#define  VIDIOC_ENUMOUTPUT 171 
#define  VIDIOC_ENUMSTD 170 
#define  VIDIOC_ENUM_FMT 169 
#define  VIDIOC_G_AUDIO 168 
#define  VIDIOC_G_AUDOUT 167 
#define  VIDIOC_G_CROP 166 
#define  VIDIOC_G_CTRL 165 
#define  VIDIOC_G_FBUF 164 
#define  VIDIOC_G_FMT 163 
#define  VIDIOC_G_FREQUENCY 162 
#define  VIDIOC_G_INPUT 161 
#define  VIDIOC_G_JPEGCOMP 160 
#define  VIDIOC_G_MODULATOR 159 
#define  VIDIOC_G_OUTPUT 158 
#define  VIDIOC_G_PARM 157 
#define  VIDIOC_G_PRIORITY 156 
#define  VIDIOC_G_STD 155 
#define  VIDIOC_G_TUNER 154 
#define  VIDIOC_OVERLAY 153 
#define  VIDIOC_QBUF 152 
#define  VIDIOC_QUERYBUF 151 
#define  VIDIOC_QUERYCAP 150 
#define  VIDIOC_QUERYCTRL 149 
#define  VIDIOC_QUERYMENU 148 
#define  VIDIOC_QUERYSTD 147 
#define  VIDIOC_REQBUFS 146 
#define  VIDIOC_STREAMOFF 145 
#define  VIDIOC_STREAMON 144 
#define  VIDIOC_S_AUDIO 143 
#define  VIDIOC_S_AUDOUT 142 
#define  VIDIOC_S_CROP 141 
#define  VIDIOC_S_CTRL 140 
#define  VIDIOC_S_FBUF 139 
#define  VIDIOC_S_FMT 138 
#define  VIDIOC_S_FREQUENCY 137 
#define  VIDIOC_S_INPUT 136 
#define  VIDIOC_S_JPEGCOMP 135 
#define  VIDIOC_S_MODULATOR 134 
#define  VIDIOC_S_OUTPUT 133 
#define  VIDIOC_S_PARM 132 
#define  VIDIOC_S_PRIORITY 131 
#define  VIDIOC_S_STD 130 
#define  VIDIOC_S_TUNER 129 
#define  VIDIOC_TRY_FMT 128 
 long cpia2_usb_stream_start (struct camera_data*,int /*<<< orphan*/ ) ; 
 long cpia2_usb_stream_stop (struct camera_data*) ; 
 long ioctl_cap_query (void*,struct camera_data*) ; 
 long ioctl_cropcap (void*,struct camera_data*) ; 
 long ioctl_dqbuf (void*,struct camera_data*,struct file*) ; 
 long ioctl_enum_fmt (void*,struct camera_data*) ; 
 long ioctl_g_ctrl (void*,struct camera_data*) ; 
 long ioctl_g_jpegcomp (void*,struct camera_data*) ; 
 long ioctl_get_channel (void*) ; 
 long ioctl_get_fmt (void*,struct camera_data*) ; 
 long ioctl_get_mbuf (void*,struct camera_data*) ; 
 long ioctl_input (unsigned int,void*,struct camera_data*) ; 
 long ioctl_mcapture (void*,struct camera_data*,struct cpia2_fh*) ; 
 long ioctl_qbuf (void*,struct camera_data*) ; 
 long ioctl_querybuf (void*,struct camera_data*) ; 
 long ioctl_querycap (void*,struct camera_data*) ; 
 long ioctl_queryctrl (void*,struct camera_data*) ; 
 long ioctl_querymenu (void*,struct camera_data*) ; 
 long ioctl_reqbufs (void*,struct camera_data*) ; 
 long ioctl_s_ctrl (void*,struct camera_data*) ; 
 long ioctl_s_jpegcomp (void*,struct camera_data*) ; 
 long ioctl_set_channel (void*) ; 
 long ioctl_set_fmt (void*,struct camera_data*,struct cpia2_fh*) ; 
 long ioctl_set_gpio (void*,struct camera_data*) ; 
 long ioctl_set_image_prop (void*,struct camera_data*) ; 
 long ioctl_set_window_size (void*,struct camera_data*,struct cpia2_fh*) ; 
 long ioctl_sync (void*,struct camera_data*) ; 
 long ioctl_try_fmt (void*,struct camera_data*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long v4l2_prio_change (int /*<<< orphan*/ *,int*,int) ; 
 long v4l2_prio_check (int /*<<< orphan*/ *,int*) ; 
 int v4l2_prio_max (int /*<<< orphan*/ *) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static long cpia2_do_ioctl(struct file *file, unsigned int cmd, void *arg)
{
	struct camera_data *cam = video_drvdata(file);
	long retval = 0;

	if (!cam)
		return -ENOTTY;

	/* make this _really_ smp-safe */
	if (mutex_lock_interruptible(&cam->busy_lock))
		return -ERESTARTSYS;

	if (!cam->present) {
		mutex_unlock(&cam->busy_lock);
		return -ENODEV;
	}

	/* Priority check */
	switch (cmd) {
	case VIDIOCSWIN:
	case VIDIOCMCAPTURE:
	case VIDIOC_S_FMT:
	{
		struct cpia2_fh *fh = file->private_data;
		retval = v4l2_prio_check(&cam->prio, &fh->prio);
		if(retval) {
			mutex_unlock(&cam->busy_lock);
			return retval;
		}
		break;
	}
	case VIDIOCGMBUF:
	case VIDIOCSYNC:
	{
		struct cpia2_fh *fh = file->private_data;
		if(fh->prio != V4L2_PRIORITY_RECORD) {
			mutex_unlock(&cam->busy_lock);
			return -EBUSY;
		}
		break;
	}
	default:
		break;
	}

	switch (cmd) {
	case VIDIOCGCAP:	/* query capabilities */
		retval = ioctl_cap_query(arg, cam);
		break;

	case VIDIOCGCHAN:	/* get video source - we are a camera, nothing else */
		retval = ioctl_get_channel(arg);
		break;
	case VIDIOCSCHAN:	/* set video source - we are a camera, nothing else */
		retval = ioctl_set_channel(arg);
		break;
	case VIDIOCGPICT:	/* image properties */
		memcpy(arg, &cam->vp, sizeof(struct video_picture));
		break;
	case VIDIOCSPICT:
		retval = ioctl_set_image_prop(arg, cam);
		break;
	case VIDIOCGWIN:	/* get/set capture window */
		memcpy(arg, &cam->vw, sizeof(struct video_window));
		break;
	case VIDIOCSWIN:
		retval = ioctl_set_window_size(arg, cam, file->private_data);
		break;
	case VIDIOCGMBUF:	/* mmap interface */
		retval = ioctl_get_mbuf(arg, cam);
		break;
	case VIDIOCMCAPTURE:
		retval = ioctl_mcapture(arg, cam, file->private_data);
		break;
	case VIDIOCSYNC:
		retval = ioctl_sync(arg, cam);
		break;
		/* pointless to implement overlay with this camera */
	case VIDIOCCAPTURE:
	case VIDIOCGFBUF:
	case VIDIOCSFBUF:
	case VIDIOCKEY:
		retval = -EINVAL;
		break;

		/* tuner interface - we have none */
	case VIDIOCGTUNER:
	case VIDIOCSTUNER:
	case VIDIOCGFREQ:
	case VIDIOCSFREQ:
		retval = -EINVAL;
		break;

		/* audio interface - we have none */
	case VIDIOCGAUDIO:
	case VIDIOCSAUDIO:
		retval = -EINVAL;
		break;

	/* CPIA2 extension to Video4Linux API */
	case CPIA2_IOC_SET_GPIO:
		retval = ioctl_set_gpio(arg, cam);
		break;
	case VIDIOC_QUERYCAP:
		retval = ioctl_querycap(arg,cam);
		break;

	case VIDIOC_ENUMINPUT:
	case VIDIOC_G_INPUT:
	case VIDIOC_S_INPUT:
		retval = ioctl_input(cmd, arg, cam);
		break;

	case VIDIOC_ENUM_FMT:
		retval = ioctl_enum_fmt(arg,cam);
		break;
	case VIDIOC_TRY_FMT:
		retval = ioctl_try_fmt(arg,cam);
		break;
	case VIDIOC_G_FMT:
		retval = ioctl_get_fmt(arg,cam);
		break;
	case VIDIOC_S_FMT:
		retval = ioctl_set_fmt(arg,cam,file->private_data);
		break;

	case VIDIOC_CROPCAP:
		retval = ioctl_cropcap(arg,cam);
		break;
	case VIDIOC_G_CROP:
	case VIDIOC_S_CROP:
		// TODO: I think cropping can be implemented - SJB
		retval = -EINVAL;
		break;

	case VIDIOC_QUERYCTRL:
		retval = ioctl_queryctrl(arg,cam);
		break;
	case VIDIOC_QUERYMENU:
		retval = ioctl_querymenu(arg,cam);
		break;
	case VIDIOC_G_CTRL:
		retval = ioctl_g_ctrl(arg,cam);
		break;
	case VIDIOC_S_CTRL:
		retval = ioctl_s_ctrl(arg,cam);
		break;

	case VIDIOC_G_JPEGCOMP:
		retval = ioctl_g_jpegcomp(arg,cam);
		break;
	case VIDIOC_S_JPEGCOMP:
		retval = ioctl_s_jpegcomp(arg,cam);
		break;

	case VIDIOC_G_PRIORITY:
	{
		struct cpia2_fh *fh = file->private_data;
		*(enum v4l2_priority*)arg = fh->prio;
		break;
	}
	case VIDIOC_S_PRIORITY:
	{
		struct cpia2_fh *fh = file->private_data;
		enum v4l2_priority prio;
		prio = *(enum v4l2_priority*)arg;
		if(cam->streaming &&
		   prio != fh->prio &&
		   fh->prio == V4L2_PRIORITY_RECORD) {
			/* Can't drop record priority while streaming */
			retval = -EBUSY;
		} else if(prio == V4L2_PRIORITY_RECORD &&
		   prio != fh->prio &&
		   v4l2_prio_max(&cam->prio) == V4L2_PRIORITY_RECORD) {
			/* Only one program can record at a time */
			retval = -EBUSY;
		} else {
			retval = v4l2_prio_change(&cam->prio, &fh->prio, prio);
		}
		break;
	}

	case VIDIOC_REQBUFS:
		retval = ioctl_reqbufs(arg,cam);
		break;
	case VIDIOC_QUERYBUF:
		retval = ioctl_querybuf(arg,cam);
		break;
	case VIDIOC_QBUF:
		retval = ioctl_qbuf(arg,cam);
		break;
	case VIDIOC_DQBUF:
		retval = ioctl_dqbuf(arg,cam,file);
		break;
	case VIDIOC_STREAMON:
	{
		int type;
		DBG("VIDIOC_STREAMON, streaming=%d\n", cam->streaming);
		type = *(int*)arg;
		if(!cam->mmapped || type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			retval = -EINVAL;

		if(!cam->streaming) {
			retval = cpia2_usb_stream_start(cam,
					  cam->params.camera_state.stream_mode);
		} else {
			retval = -EINVAL;
		}

		break;
	}
	case VIDIOC_STREAMOFF:
	{
		int type;
		DBG("VIDIOC_STREAMOFF, streaming=%d\n", cam->streaming);
		type = *(int*)arg;
		if(!cam->mmapped || type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			retval = -EINVAL;

		if(cam->streaming) {
			retval = cpia2_usb_stream_stop(cam);
		} else {
			retval = -EINVAL;
		}

		break;
	}

	case VIDIOC_ENUMOUTPUT:
	case VIDIOC_G_OUTPUT:
	case VIDIOC_S_OUTPUT:
	case VIDIOC_G_MODULATOR:
	case VIDIOC_S_MODULATOR:

	case VIDIOC_ENUMAUDIO:
	case VIDIOC_G_AUDIO:
	case VIDIOC_S_AUDIO:

	case VIDIOC_ENUMAUDOUT:
	case VIDIOC_G_AUDOUT:
	case VIDIOC_S_AUDOUT:

	case VIDIOC_ENUMSTD:
	case VIDIOC_QUERYSTD:
	case VIDIOC_G_STD:
	case VIDIOC_S_STD:

	case VIDIOC_G_TUNER:
	case VIDIOC_S_TUNER:
	case VIDIOC_G_FREQUENCY:
	case VIDIOC_S_FREQUENCY:

	case VIDIOC_OVERLAY:
	case VIDIOC_G_FBUF:
	case VIDIOC_S_FBUF:

	case VIDIOC_G_PARM:
	case VIDIOC_S_PARM:
		retval = -EINVAL;
		break;
	default:
		retval = -ENOIOCTLCMD;
		break;
	}

	mutex_unlock(&cam->busy_lock);
	return retval;
}
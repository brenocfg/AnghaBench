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
struct video_window {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  clipcount; int /*<<< orphan*/  flags; int /*<<< orphan*/  chromakey; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct video_picture {int dummy; } ;
struct video_mmap {int frame; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct video_mbuf {int size; int frames; int* offsets; } ;
struct video_device {int dummy; } ;
struct video_channel {int /*<<< orphan*/  channel; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  tuners; int /*<<< orphan*/  flags; } ;
struct video_capability {int channels; int /*<<< orphan*/  minheight; int /*<<< orphan*/  minwidth; int /*<<< orphan*/  maxheight; int /*<<< orphan*/  maxwidth; int /*<<< orphan*/  audios; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct video_buffer {int size; int frames; int* offsets; } ;
struct usb_se401 {char* camera_name; int maxframesize; int framecount; TYPE_1__* frame; int /*<<< orphan*/  streaming; int /*<<< orphan*/  cheight; int /*<<< orphan*/  cwidth; int /*<<< orphan*/ * height; int /*<<< orphan*/ * width; int /*<<< orphan*/  sizes; int /*<<< orphan*/  dev; } ;
struct file {struct video_device* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  grabstate; } ;

/* Variables and functions */
 long EBUSY ; 
 long EINVAL ; 
 long EIO ; 
 long ENOIOCTLCMD ; 
 int /*<<< orphan*/  FRAME_READY ; 
 int /*<<< orphan*/  FRAME_UNUSED ; 
 int SE401_NUMFRAMES ; 
 int /*<<< orphan*/  VIDEO_PALETTE_RGB24 ; 
 int /*<<< orphan*/  VIDEO_TYPE_CAMERA ; 
#define  VIDIOCCAPTURE 147 
#define  VIDIOCGAUDIO 146 
#define  VIDIOCGCAP 145 
#define  VIDIOCGCHAN 144 
#define  VIDIOCGFBUF 143 
#define  VIDIOCGFREQ 142 
#define  VIDIOCGMBUF 141 
#define  VIDIOCGPICT 140 
#define  VIDIOCGTUNER 139 
#define  VIDIOCGWIN 138 
#define  VIDIOCKEY 137 
#define  VIDIOCMCAPTURE 136 
#define  VIDIOCSAUDIO 135 
#define  VIDIOCSCHAN 134 
#define  VIDIOCSFBUF 133 
#define  VIDIOCSFREQ 132 
#define  VIDIOCSPICT 131 
#define  VIDIOCSTUNER 130 
#define  VIDIOCSWIN 129 
#define  VIDIOCSYNC 128 
 int /*<<< orphan*/  VID_TYPE_CAPTURE ; 
 int /*<<< orphan*/  memset (struct video_mbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  se401_auto_resetlevel (struct usb_se401*) ; 
 int /*<<< orphan*/  se401_get_pict (struct usb_se401*,struct video_picture*) ; 
 int se401_newframe (struct usb_se401*,int) ; 
 int /*<<< orphan*/  se401_send_pict (struct usb_se401*) ; 
 int /*<<< orphan*/  se401_set_pict (struct usb_se401*,struct video_picture*) ; 
 int /*<<< orphan*/  se401_set_size (struct usb_se401*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se401_start_stream (struct usb_se401*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static long se401_do_ioctl(struct file *file, unsigned int cmd, void *arg)
{
	struct video_device *vdev = file->private_data;
	struct usb_se401 *se401 = (struct usb_se401 *)vdev;

	if (!se401->dev)
		return -EIO;

	switch (cmd) {
	case VIDIOCGCAP:
	{
		struct video_capability *b = arg;
		strcpy(b->name, se401->camera_name);
		b->type = VID_TYPE_CAPTURE;
		b->channels = 1;
		b->audios = 0;
		b->maxwidth = se401->width[se401->sizes-1];
		b->maxheight = se401->height[se401->sizes-1];
		b->minwidth = se401->width[0];
		b->minheight = se401->height[0];
		return 0;
	}
	case VIDIOCGCHAN:
	{
		struct video_channel *v = arg;

		if (v->channel != 0)
			return -EINVAL;
		v->flags = 0;
		v->tuners = 0;
		v->type = VIDEO_TYPE_CAMERA;
		strcpy(v->name, "Camera");
		return 0;
	}
	case VIDIOCSCHAN:
	{
		struct video_channel *v = arg;

		if (v->channel != 0)
			return -EINVAL;
		return 0;
	}
	case VIDIOCGPICT:
	{
		struct video_picture *p = arg;

		se401_get_pict(se401, p);
		return 0;
	}
	case VIDIOCSPICT:
	{
		struct video_picture *p = arg;

		if (se401_set_pict(se401, p))
			return -EINVAL;
		return 0;
	}
	case VIDIOCSWIN:
	{
		struct video_window *vw = arg;

		if (vw->flags)
			return -EINVAL;
		if (vw->clipcount)
			return -EINVAL;
		if (se401_set_size(se401, vw->width, vw->height))
			return -EINVAL;
		return 0;
	}
	case VIDIOCGWIN:
	{
		struct video_window *vw = arg;

		vw->x = 0;               /* FIXME */
		vw->y = 0;
		vw->chromakey = 0;
		vw->flags = 0;
		vw->clipcount = 0;
		vw->width = se401->cwidth;
		vw->height = se401->cheight;
		return 0;
	}
	case VIDIOCGMBUF:
	{
		struct video_mbuf *vm = arg;
		int i;

		memset(vm, 0, sizeof(*vm));
		vm->size = SE401_NUMFRAMES * se401->maxframesize;
		vm->frames = SE401_NUMFRAMES;
		for (i = 0; i < SE401_NUMFRAMES; i++)
			vm->offsets[i] = se401->maxframesize * i;
		return 0;
	}
	case VIDIOCMCAPTURE:
	{
		struct video_mmap *vm = arg;

		if (vm->format != VIDEO_PALETTE_RGB24)
			return -EINVAL;
		if (vm->frame >= SE401_NUMFRAMES)
			return -EINVAL;
		if (se401->frame[vm->frame].grabstate != FRAME_UNUSED)
			return -EBUSY;

		/* Is this according to the v4l spec??? */
		if (se401_set_size(se401, vm->width, vm->height))
			return -EINVAL;
		se401->frame[vm->frame].grabstate = FRAME_READY;

		if (!se401->streaming)
			se401_start_stream(se401);

		/* Set the picture properties */
		if (se401->framecount == 0)
			se401_send_pict(se401);
		/* Calibrate the reset level after a few frames. */
		if (se401->framecount % 20 == 1)
			se401_auto_resetlevel(se401);

		return 0;
	}
	case VIDIOCSYNC:
	{
		int *frame = arg;
		int ret = 0;

		if (*frame < 0 || *frame >= SE401_NUMFRAMES)
			return -EINVAL;

		ret = se401_newframe(se401, *frame);
		se401->frame[*frame].grabstate = FRAME_UNUSED;
		return ret;
	}
	case VIDIOCGFBUF:
	{
		struct video_buffer *vb = arg;

		memset(vb, 0, sizeof(*vb));
		return 0;
	}
	case VIDIOCKEY:
		return 0;
	case VIDIOCCAPTURE:
		return -EINVAL;
	case VIDIOCSFBUF:
		return -EINVAL;
	case VIDIOCGTUNER:
	case VIDIOCSTUNER:
		return -EINVAL;
	case VIDIOCGFREQ:
	case VIDIOCSFREQ:
		return -EINVAL;
	case VIDIOCGAUDIO:
	case VIDIOCSAUDIO:
		return -EINVAL;
	default:
		return -ENOIOCTLCMD;
	} /* end switch */

	return 0;
}
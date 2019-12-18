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
struct video_mmap {int format; int frame; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct video_mbuf {int size; int frames; int* offsets; } ;
struct video_device {int dummy; } ;
struct video_channel {int /*<<< orphan*/  channel; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  tuners; int /*<<< orphan*/  flags; } ;
struct video_capability {int channels; int maxwidth; int maxheight; int minwidth; int minheight; int /*<<< orphan*/  audios; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct video_buffer {int size; int frames; int* offsets; } ;
struct usb_stv {char* camera_name; int maxwidth; int maxheight; int maxframesize; TYPE_1__* frame; int /*<<< orphan*/  streaming; int /*<<< orphan*/  vwidth; int /*<<< orphan*/  vheight; int /*<<< orphan*/  udev; } ;
struct file {struct video_device* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  grabstate; } ;

/* Variables and functions */
 long EBUSY ; 
 long EINVAL ; 
 long EIO ; 
 long ENOIOCTLCMD ; 
 int /*<<< orphan*/  FRAME_ERROR ; 
 int /*<<< orphan*/  FRAME_GRABBING ; 
 int /*<<< orphan*/  FRAME_READY ; 
 int /*<<< orphan*/  FRAME_UNUSED ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
 int STV680_NUMFRAMES ; 
 int STV_VIDEO_PALETTE ; 
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
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stv680_get_pict (struct usb_stv*,struct video_picture*) ; 
 int stv680_newframe (struct usb_stv*,int) ; 
 int /*<<< orphan*/  stv680_set_pict (struct usb_stv*,struct video_picture*) ; 
 int /*<<< orphan*/  stv680_set_size (struct usb_stv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv680_start_stream (struct usb_stv*) ; 
 int swapRGB ; 
 int /*<<< orphan*/  swapRGB_on ; 
 struct usb_stv* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static long stv680_do_ioctl(struct file *file, unsigned int cmd, void *arg)
{
	struct video_device *vdev = file->private_data;
	struct usb_stv *stv680 = video_get_drvdata(vdev);

	if (!stv680->udev)
		return -EIO;

	switch (cmd) {
	case VIDIOCGCAP:{
			struct video_capability *b = arg;

			strcpy (b->name, stv680->camera_name);
			b->type = VID_TYPE_CAPTURE;
			b->channels = 1;
			b->audios = 0;
			b->maxwidth = stv680->maxwidth;
			b->maxheight = stv680->maxheight;
			b->minwidth = stv680->maxwidth / 2;
			b->minheight = stv680->maxheight / 2;
			return 0;
		}
	case VIDIOCGCHAN:{
			struct video_channel *v = arg;

			if (v->channel != 0)
				return -EINVAL;
			v->flags = 0;
			v->tuners = 0;
			v->type = VIDEO_TYPE_CAMERA;
			strcpy (v->name, "STV Camera");
			return 0;
		}
	case VIDIOCSCHAN:{
			struct video_channel *v = arg;
			if (v->channel != 0)
				return -EINVAL;
			return 0;
		}
	case VIDIOCGPICT:{
			struct video_picture *p = arg;

			stv680_get_pict (stv680, p);
			return 0;
		}
	case VIDIOCSPICT:{
			struct video_picture *p = arg;

			if (stv680_set_pict (stv680, p))
				return -EINVAL;
			return 0;
		}
	case VIDIOCSWIN:{
			struct video_window *vw = arg;

			if (vw->flags)
				return -EINVAL;
			if (vw->clipcount)
				return -EINVAL;
			if (vw->width != stv680->vwidth) {
				if (stv680_set_size (stv680, vw->width, vw->height)) {
					PDEBUG (2, "STV(e): failed (from user) set size in VIDIOCSWIN");
					return -EINVAL;
				}
			}
			return 0;
		}
	case VIDIOCGWIN:{
			struct video_window *vw = arg;

			vw->x = 0;	/* FIXME */
			vw->y = 0;
			vw->chromakey = 0;
			vw->flags = 0;
			vw->clipcount = 0;
			vw->width = stv680->vwidth;
			vw->height = stv680->vheight;
			return 0;
		}
	case VIDIOCGMBUF:{
			struct video_mbuf *vm = arg;
			int i;

			memset (vm, 0, sizeof (*vm));
			vm->size = STV680_NUMFRAMES * stv680->maxframesize;
			vm->frames = STV680_NUMFRAMES;
			for (i = 0; i < STV680_NUMFRAMES; i++)
				vm->offsets[i] = stv680->maxframesize * i;
			return 0;
		}
	case VIDIOCMCAPTURE:{
			struct video_mmap *vm = arg;

			if (vm->format != STV_VIDEO_PALETTE) {
				PDEBUG (2, "STV(i): VIDIOCMCAPTURE vm.format (%i) != VIDEO_PALETTE (%i)",
					vm->format, STV_VIDEO_PALETTE);
				if ((vm->format == 3) && (swapRGB_on == 0))  {
					PDEBUG (2, "STV(i): VIDIOCMCAPTURE swapRGB is (auto) ON");
					/* this may fix those apps (e.g., xawtv) that want BGR */
					swapRGB = 1;
				}
				return -EINVAL;
			}
			if (vm->frame >= STV680_NUMFRAMES) {
				PDEBUG (2, "STV(e): VIDIOCMCAPTURE vm.frame > NUMFRAMES");
				return -EINVAL;
			}
			if ((stv680->frame[vm->frame].grabstate == FRAME_ERROR)
			    || (stv680->frame[vm->frame].grabstate == FRAME_GRABBING)) {
				PDEBUG (2, "STV(e): VIDIOCMCAPTURE grabstate (%i) error",
					stv680->frame[vm->frame].grabstate);
				return -EBUSY;
			}
			/* Is this according to the v4l spec??? */
			if (stv680->vwidth != vm->width) {
				if (stv680_set_size (stv680, vm->width, vm->height)) {
					PDEBUG (2, "STV(e): VIDIOCMCAPTURE set_size failed");
					return -EINVAL;
				}
			}
			stv680->frame[vm->frame].grabstate = FRAME_READY;

			if (!stv680->streaming)
				stv680_start_stream (stv680);

			return 0;
		}
	case VIDIOCSYNC:{
			int *frame = arg;
			int ret = 0;

			if (*frame < 0 || *frame >= STV680_NUMFRAMES) {
				PDEBUG (2, "STV(e): Bad frame # in VIDIOCSYNC");
				return -EINVAL;
			}
			ret = stv680_newframe (stv680, *frame);
			stv680->frame[*frame].grabstate = FRAME_UNUSED;
			return ret;
		}
	case VIDIOCGFBUF:{
			struct video_buffer *vb = arg;

			memset (vb, 0, sizeof (*vb));
			return 0;
		}
	case VIDIOCKEY:
		return 0;
	case VIDIOCCAPTURE:
		{
			PDEBUG (2, "STV(e): VIDIOCCAPTURE failed");
			return -EINVAL;
		}
	case VIDIOCSFBUF:
	case VIDIOCGTUNER:
	case VIDIOCSTUNER:
	case VIDIOCGFREQ:
	case VIDIOCSFREQ:
	case VIDIOCGAUDIO:
	case VIDIOCSAUDIO:
		return -EINVAL;
	default:
		return -ENOIOCTLCMD;
	}			/* end switch */

	return 0;
}
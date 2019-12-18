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
struct video_window {int height; int width; int /*<<< orphan*/  clipcount; int /*<<< orphan*/  flags; } ;
struct video_tuner {int /*<<< orphan*/  mode; int /*<<< orphan*/  tuner; int /*<<< orphan*/  flags; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  name; } ;
struct video_picture {int colour; int hue; int brightness; int contrast; int whiteness; int depth; int /*<<< orphan*/  palette; } ;
struct video_device {int dummy; } ;
struct video_channel {int /*<<< orphan*/  channel; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  tuners; int /*<<< orphan*/  flags; } ;
struct video_capability {int type; int channels; int maxwidth; int maxheight; int minwidth; int minheight; int /*<<< orphan*/  audios; int /*<<< orphan*/  name; } ;
struct qcam_device {int brightness; int contrast; int whitebal; int bpp; int width; int height; int transfer_scale; int /*<<< orphan*/  status; int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 long ENOIOCTLCMD ; 
 int /*<<< orphan*/  QC_PARAM_CHANGE ; 
 int /*<<< orphan*/  VIDEO_MODE_AUTO ; 
 int /*<<< orphan*/  VIDEO_PALETTE_GREY ; 
 int /*<<< orphan*/  VIDEO_TYPE_CAMERA ; 
#define  VIDIOCCAPTURE 144 
#define  VIDIOCGAUDIO 143 
#define  VIDIOCGCAP 142 
#define  VIDIOCGCHAN 141 
#define  VIDIOCGFBUF 140 
#define  VIDIOCGFREQ 139 
#define  VIDIOCGPICT 138 
#define  VIDIOCGTUNER 137 
#define  VIDIOCGWIN 136 
#define  VIDIOCKEY 135 
#define  VIDIOCSAUDIO 134 
#define  VIDIOCSCHAN 133 
#define  VIDIOCSFBUF 132 
#define  VIDIOCSFREQ 131 
#define  VIDIOCSPICT 130 
#define  VIDIOCSTUNER 129 
#define  VIDIOCSWIN 128 
 int VID_TYPE_CAPTURE ; 
 int VID_TYPE_MONOCHROME ; 
 int VID_TYPE_SCALES ; 
 int /*<<< orphan*/  memset (struct video_window*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qc_setscanmode (struct qcam_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static long qcam_do_ioctl(struct file *file, unsigned int cmd, void *arg)
{
	struct video_device *dev = video_devdata(file);
	struct qcam_device *qcam=(struct qcam_device *)dev;

	switch(cmd)
	{
		case VIDIOCGCAP:
		{
			struct video_capability *b = arg;
			strcpy(b->name, "Quickcam");
			b->type = VID_TYPE_CAPTURE|VID_TYPE_SCALES|VID_TYPE_MONOCHROME;
			b->channels = 1;
			b->audios = 0;
			b->maxwidth = 320;
			b->maxheight = 240;
			b->minwidth = 80;
			b->minheight = 60;
			return 0;
		}
		case VIDIOCGCHAN:
		{
			struct video_channel *v = arg;
			if(v->channel!=0)
				return -EINVAL;
			v->flags=0;
			v->tuners=0;
			/* Good question.. its composite or SVHS so.. */
			v->type = VIDEO_TYPE_CAMERA;
			strcpy(v->name, "Camera");
			return 0;
		}
		case VIDIOCSCHAN:
		{
			struct video_channel *v = arg;
			if(v->channel!=0)
				return -EINVAL;
			return 0;
		}
		case VIDIOCGTUNER:
		{
			struct video_tuner *v = arg;
			if(v->tuner)
				return -EINVAL;
			strcpy(v->name, "Format");
			v->rangelow=0;
			v->rangehigh=0;
			v->flags= 0;
			v->mode = VIDEO_MODE_AUTO;
			return 0;
		}
		case VIDIOCSTUNER:
		{
			struct video_tuner *v = arg;
			if(v->tuner)
				return -EINVAL;
			if(v->mode!=VIDEO_MODE_AUTO)
				return -EINVAL;
			return 0;
		}
		case VIDIOCGPICT:
		{
			struct video_picture *p = arg;
			p->colour=0x8000;
			p->hue=0x8000;
			p->brightness=qcam->brightness<<8;
			p->contrast=qcam->contrast<<8;
			p->whiteness=qcam->whitebal<<8;
			p->depth=qcam->bpp;
			p->palette=VIDEO_PALETTE_GREY;
			return 0;
		}
		case VIDIOCSPICT:
		{
			struct video_picture *p = arg;
			if(p->palette!=VIDEO_PALETTE_GREY)
				return -EINVAL;
			if(p->depth!=4 && p->depth!=6)
				return -EINVAL;

			/*
			 *	Now load the camera.
			 */

			qcam->brightness = p->brightness>>8;
			qcam->contrast = p->contrast>>8;
			qcam->whitebal = p->whiteness>>8;
			qcam->bpp = p->depth;

			mutex_lock(&qcam->lock);
			qc_setscanmode(qcam);
			mutex_unlock(&qcam->lock);
			qcam->status |= QC_PARAM_CHANGE;

			return 0;
		}
		case VIDIOCSWIN:
		{
			struct video_window *vw = arg;
			if(vw->flags)
				return -EINVAL;
			if(vw->clipcount)
				return -EINVAL;
			if(vw->height<60||vw->height>240)
				return -EINVAL;
			if(vw->width<80||vw->width>320)
				return -EINVAL;

			qcam->width = 320;
			qcam->height = 240;
			qcam->transfer_scale = 4;

			if(vw->width>=160 && vw->height>=120)
			{
				qcam->transfer_scale = 2;
			}
			if(vw->width>=320 && vw->height>=240)
			{
				qcam->width = 320;
				qcam->height = 240;
				qcam->transfer_scale = 1;
			}
			mutex_lock(&qcam->lock);
			qc_setscanmode(qcam);
			mutex_unlock(&qcam->lock);

			/* We must update the camera before we grab. We could
			   just have changed the grab size */
			qcam->status |= QC_PARAM_CHANGE;

			/* Ok we figured out what to use from our wide choice */
			return 0;
		}
		case VIDIOCGWIN:
		{
			struct video_window *vw = arg;
			memset(vw, 0, sizeof(*vw));
			vw->width=qcam->width/qcam->transfer_scale;
			vw->height=qcam->height/qcam->transfer_scale;
			return 0;
		}
		case VIDIOCKEY:
			return 0;
		case VIDIOCCAPTURE:
		case VIDIOCGFBUF:
		case VIDIOCSFBUF:
		case VIDIOCGFREQ:
		case VIDIOCSFREQ:
		case VIDIOCGAUDIO:
		case VIDIOCSAUDIO:
			return -EINVAL;
		default:
			return -ENOIOCTLCMD;
	}
	return 0;
}
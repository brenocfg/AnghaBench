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
struct video_tuner {int flags; int mode; int /*<<< orphan*/  tuner; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  name; } ;
struct video_picture {int depth; int brightness; int hue; int colour; int contrast; int /*<<< orphan*/  palette; } ;
struct video_device {int dummy; } ;
struct video_channel {int channel; int tuners; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; } ;
struct video_capability {int type; int channels; int maxwidth; int maxheight; int minwidth; int minheight; int /*<<< orphan*/  audios; int /*<<< orphan*/  name; } ;
struct pms_device {int width; int height; int /*<<< orphan*/  lock; struct video_picture picture; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 long ENOIOCTLCMD ; 
#define  VIDEO_MODE_AUTO 148 
#define  VIDEO_MODE_NTSC 147 
#define  VIDEO_MODE_PAL 146 
#define  VIDEO_MODE_SECAM 145 
 int /*<<< orphan*/  VIDEO_PALETTE_RGB555 ; 
 int /*<<< orphan*/  VIDEO_PALETTE_RGB565 ; 
 int VIDEO_TUNER_NTSC ; 
 int VIDEO_TUNER_PAL ; 
 int VIDEO_TUNER_SECAM ; 
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
 int VID_TYPE_SCALES ; 
 int /*<<< orphan*/  memset (struct video_window*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pms_brightness (int) ; 
 int /*<<< orphan*/  pms_colour (int) ; 
 int /*<<< orphan*/  pms_contrast (int) ; 
 int /*<<< orphan*/  pms_format (int) ; 
 int /*<<< orphan*/  pms_framerate (int) ; 
 int /*<<< orphan*/  pms_hue (int) ; 
 int /*<<< orphan*/  pms_resolution (int,int) ; 
 int /*<<< orphan*/  pms_secamcross (int) ; 
 int /*<<< orphan*/  pms_vcrinput (int) ; 
 int /*<<< orphan*/  pms_videosource (int) ; 
 int /*<<< orphan*/  standard ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static long pms_do_ioctl(struct file *file, unsigned int cmd, void *arg)
{
	struct video_device *dev = video_devdata(file);
	struct pms_device *pd=(struct pms_device *)dev;

	switch(cmd)
	{
		case VIDIOCGCAP:
		{
			struct video_capability *b = arg;
			strcpy(b->name, "Mediavision PMS");
			b->type = VID_TYPE_CAPTURE|VID_TYPE_SCALES;
			b->channels = 4;
			b->audios = 0;
			b->maxwidth = 640;
			b->maxheight = 480;
			b->minwidth = 16;
			b->minheight = 16;
			return 0;
		}
		case VIDIOCGCHAN:
		{
			struct video_channel *v = arg;
			if(v->channel<0 || v->channel>3)
				return -EINVAL;
			v->flags=0;
			v->tuners=1;
			/* Good question.. its composite or SVHS so.. */
			v->type = VIDEO_TYPE_CAMERA;
			switch(v->channel)
			{
				case 0:
					strcpy(v->name, "Composite");break;
				case 1:
					strcpy(v->name, "SVideo");break;
				case 2:
					strcpy(v->name, "Composite(VCR)");break;
				case 3:
					strcpy(v->name, "SVideo(VCR)");break;
			}
			return 0;
		}
		case VIDIOCSCHAN:
		{
			struct video_channel *v = arg;
			if(v->channel<0 || v->channel>3)
				return -EINVAL;
			mutex_lock(&pd->lock);
			pms_videosource(v->channel&1);
			pms_vcrinput(v->channel>>1);
			mutex_unlock(&pd->lock);
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
			v->flags= VIDEO_TUNER_PAL|VIDEO_TUNER_NTSC|VIDEO_TUNER_SECAM;
			switch(standard)
			{
				case 0:
					v->mode = VIDEO_MODE_AUTO;
					break;
				case 1:
					v->mode = VIDEO_MODE_NTSC;
					break;
				case 2:
					v->mode = VIDEO_MODE_PAL;
					break;
				case 3:
					v->mode = VIDEO_MODE_SECAM;
					break;
			}
			return 0;
		}
		case VIDIOCSTUNER:
		{
			struct video_tuner *v = arg;
			if(v->tuner)
				return -EINVAL;
			mutex_lock(&pd->lock);
			switch(v->mode)
			{
				case VIDEO_MODE_AUTO:
					pms_framerate(25);
					pms_secamcross(0);
					pms_format(0);
					break;
				case VIDEO_MODE_NTSC:
					pms_framerate(30);
					pms_secamcross(0);
					pms_format(1);
					break;
				case VIDEO_MODE_PAL:
					pms_framerate(25);
					pms_secamcross(0);
					pms_format(2);
					break;
				case VIDEO_MODE_SECAM:
					pms_framerate(25);
					pms_secamcross(1);
					pms_format(2);
					break;
				default:
					mutex_unlock(&pd->lock);
					return -EINVAL;
			}
			mutex_unlock(&pd->lock);
			return 0;
		}
		case VIDIOCGPICT:
		{
			struct video_picture *p = arg;
			*p = pd->picture;
			return 0;
		}
		case VIDIOCSPICT:
		{
			struct video_picture *p = arg;
			if(!((p->palette==VIDEO_PALETTE_RGB565 && p->depth==16)
			    ||(p->palette==VIDEO_PALETTE_RGB555 && p->depth==15)))
				return -EINVAL;
			pd->picture= *p;

			/*
			 *	Now load the card.
			 */

			mutex_lock(&pd->lock);
			pms_brightness(p->brightness>>8);
			pms_hue(p->hue>>8);
			pms_colour(p->colour>>8);
			pms_contrast(p->contrast>>8);
			mutex_unlock(&pd->lock);
			return 0;
		}
		case VIDIOCSWIN:
		{
			struct video_window *vw = arg;
			if(vw->flags)
				return -EINVAL;
			if(vw->clipcount)
				return -EINVAL;
			if(vw->height<16||vw->height>480)
				return -EINVAL;
			if(vw->width<16||vw->width>640)
				return -EINVAL;
			pd->width=vw->width;
			pd->height=vw->height;
			mutex_lock(&pd->lock);
			pms_resolution(pd->width, pd->height);
			mutex_unlock(&pd->lock);			/* Ok we figured out what to use from our wide choice */
			return 0;
		}
		case VIDIOCGWIN:
		{
			struct video_window *vw = arg;
			memset(vw,0,sizeof(*vw));
			vw->width=pd->width;
			vw->height=pd->height;
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
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cx18_stream {int type; char* name; TYPE_3__* video_dev; scalar_t__ buffers; int /*<<< orphan*/ * dvb; struct cx18* cx; } ;
struct cx18_dvb {int dummy; } ;
struct TYPE_7__ {char* name; } ;
struct cx18 {int v4l2_cap; int instance; scalar_t__* stream_buffers; TYPE_2__ v4l2_dev; TYPE_1__* card; struct cx18_stream* streams; } ;
struct TYPE_9__ {int num_offset; char* name; scalar_t__ dma; } ;
struct TYPE_8__ {int num; int /*<<< orphan*/  tvnorms; int /*<<< orphan*/  release; int /*<<< orphan*/ * fops; TYPE_2__* v4l2_dev; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int hw_all; } ;

/* Variables and functions */
 int CX18_ENC_STREAM_TYPE_RAD ; 
 int CX18_ENC_STREAM_TYPE_TS ; 
 int CX18_ENC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  CX18_ERR (char*,char*) ; 
 int CX18_HW_DVB ; 
 int /*<<< orphan*/  CX18_INFO (char*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PCI_DMA_NONE ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_SLICED_VBI_CAPTURE ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int cx18_first_minor ; 
 int /*<<< orphan*/  cx18_set_funcs (TYPE_3__*) ; 
 TYPE_4__* cx18_stream_info ; 
 int /*<<< orphan*/  cx18_stream_init (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_v4l2_enc_fops ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 TYPE_3__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release ; 

__attribute__((used)) static int cx18_prep_dev(struct cx18 *cx, int type)
{
	struct cx18_stream *s = &cx->streams[type];
	u32 cap = cx->v4l2_cap;
	int num_offset = cx18_stream_info[type].num_offset;
	int num = cx->instance + cx18_first_minor + num_offset;

	/*
	 * These five fields are always initialized.
	 * For analog capture related streams, if video_dev == NULL then the
	 * stream is not in use.
	 * For the TS stream, if dvb == NULL then the stream is not in use.
	 * In those cases no other fields but these four can be used.
	 */
	s->video_dev = NULL;
	s->dvb = NULL;
	s->cx = cx;
	s->type = type;
	s->name = cx18_stream_info[type].name;

	/* Check whether the radio is supported */
	if (type == CX18_ENC_STREAM_TYPE_RAD && !(cap & V4L2_CAP_RADIO))
		return 0;

	/* Check whether VBI is supported */
	if (type == CX18_ENC_STREAM_TYPE_VBI &&
	    !(cap & (V4L2_CAP_VBI_CAPTURE | V4L2_CAP_SLICED_VBI_CAPTURE)))
		return 0;

	/* User explicitly selected 0 buffers for these streams, so don't
	   create them. */
	if (cx18_stream_info[type].dma != PCI_DMA_NONE &&
	    cx->stream_buffers[type] == 0) {
		CX18_INFO("Disabled %s device\n", cx18_stream_info[type].name);
		return 0;
	}

	cx18_stream_init(cx, type);

	/* Allocate the cx18_dvb struct only for the TS on cards with DTV */
	if (type == CX18_ENC_STREAM_TYPE_TS) {
		if (cx->card->hw_all & CX18_HW_DVB) {
			s->dvb = kzalloc(sizeof(struct cx18_dvb), GFP_KERNEL);
			if (s->dvb == NULL) {
				CX18_ERR("Couldn't allocate cx18_dvb structure"
					 " for %s\n", s->name);
				return -ENOMEM;
			}
		} else {
			/* Don't need buffers for the TS, if there is no DVB */
			s->buffers = 0;
		}
	}

	if (num_offset == -1)
		return 0;

	/* allocate and initialize the v4l2 video device structure */
	s->video_dev = video_device_alloc();
	if (s->video_dev == NULL) {
		CX18_ERR("Couldn't allocate v4l2 video_device for %s\n",
				s->name);
		return -ENOMEM;
	}

	snprintf(s->video_dev->name, sizeof(s->video_dev->name), "%s %s",
		 cx->v4l2_dev.name, s->name);

	s->video_dev->num = num;
	s->video_dev->v4l2_dev = &cx->v4l2_dev;
	s->video_dev->fops = &cx18_v4l2_enc_fops;
	s->video_dev->release = video_device_release;
	s->video_dev->tvnorms = V4L2_STD_ALL;
	cx18_set_funcs(s->video_dev);
	return 0;
}
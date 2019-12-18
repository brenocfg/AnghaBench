#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct video_device_shadow {int /*<<< orphan*/  ctrl_handler; } ;
struct ivtv_stream {int type; char* name; TYPE_3__* vdev; struct ivtv* itv; } ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_8__ {scalar_t__* kilobytes; } ;
struct ivtv {int instance; int v4l2_cap; TYPE_2__ v4l2_dev; TYPE_1__ options; struct ivtv_stream* streams; } ;
struct TYPE_11__ {int num_offset; char* name; scalar_t__ dma; int /*<<< orphan*/  fops; } ;
struct TYPE_10__ {int num; int /*<<< orphan*/  tvnorms; int /*<<< orphan*/  (* release ) (TYPE_3__*) ;int /*<<< orphan*/  fops; TYPE_2__* v4l2_dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IVTV_DEC_STREAM_TYPE_MPG ; 
 int IVTV_ENC_STREAM_TYPE_RAD ; 
 int /*<<< orphan*/  IVTV_ERR (char*,char*) ; 
 int /*<<< orphan*/  IVTV_INFO (char*,char*) ; 
 scalar_t__ PCI_DMA_NONE ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int ivtv_first_minor ; 
 int /*<<< orphan*/  ivtv_set_funcs (TYPE_3__*) ; 
 TYPE_6__* ivtv_stream_info ; 
 int /*<<< orphan*/  ivtv_stream_init (struct ivtv*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 TYPE_3__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (TYPE_3__*) ; 
 struct video_device_shadow* video_device_shadow_get (TYPE_3__*) ; 

__attribute__((used)) static int ivtv_prep_dev(struct ivtv *itv, int type)
{
	struct ivtv_stream *s = &itv->streams[type];
	int num_offset = ivtv_stream_info[type].num_offset;
	int num = itv->instance + ivtv_first_minor + num_offset;
	struct video_device_shadow *shvdev;

	/* These four fields are always initialized. If vdev == NULL, then
	   this stream is not in use. In that case no other fields but these
	   four can be used. */
	s->vdev = NULL;
	s->itv = itv;
	s->type = type;
	s->name = ivtv_stream_info[type].name;

	/* Check whether the radio is supported */
	if (type == IVTV_ENC_STREAM_TYPE_RAD && !(itv->v4l2_cap & V4L2_CAP_RADIO))
		return 0;
	if (type >= IVTV_DEC_STREAM_TYPE_MPG && !(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		return 0;

	/* User explicitly selected 0 buffers for these streams, so don't
	   create them. */
	if (ivtv_stream_info[type].dma != PCI_DMA_NONE &&
	    itv->options.kilobytes[type] == 0) {
		IVTV_INFO("Disabled %s device\n", ivtv_stream_info[type].name);
		return 0;
	}

	ivtv_stream_init(itv, type);

	/* allocate and initialize the v4l2 video device structure */
	s->vdev = video_device_alloc();
	if (s->vdev == NULL) {
		IVTV_ERR("Couldn't allocate v4l2 video_device for %s\n", s->name);
		return -ENOMEM;
	}
	shvdev = video_device_shadow_get(s->vdev);
	if (shvdev == NULL) {
		IVTV_ERR("Couldn't allocate v4l2 video_device_shadow for %s\n", s->name);
		video_device_release(s->vdev);
		return -ENOMEM;
	}

	snprintf(s->vdev->name, sizeof(s->vdev->name), "%s %s",
			itv->v4l2_dev.name, s->name);

	s->vdev->num = num;
	s->vdev->v4l2_dev = &itv->v4l2_dev;
	shvdev->ctrl_handler = itv->v4l2_dev.ctrl_handler;
	s->vdev->fops = ivtv_stream_info[type].fops;
	s->vdev->release = video_device_release;
	s->vdev->tvnorms = V4L2_STD_ALL;
	ivtv_set_funcs(s->vdev);
	return 0;
}
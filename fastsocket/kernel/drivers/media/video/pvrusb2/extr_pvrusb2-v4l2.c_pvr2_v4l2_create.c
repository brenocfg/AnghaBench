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
struct TYPE_4__ {TYPE_1__* mc_head; int /*<<< orphan*/  check_func; } ;
struct pvr2_v4l2 {void* dev_radio; TYPE_2__ channel; void* dev_video; } ;
struct pvr2_context {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hdw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PVR2_CVAL_INPUT_RADIO ; 
 int /*<<< orphan*/  PVR2_TRACE_STRUCT ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_channel_init (TYPE_2__*,struct pvr2_context*) ; 
 int pvr2_hdw_get_input_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_v4l2*) ; 
 int /*<<< orphan*/  pvr2_v4l2_destroy_no_lock (struct pvr2_v4l2*) ; 
 int /*<<< orphan*/  pvr2_v4l2_dev_init (void*,struct pvr2_v4l2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_v4l2_internal_check ; 

struct pvr2_v4l2 *pvr2_v4l2_create(struct pvr2_context *mnp)
{
	struct pvr2_v4l2 *vp;

	vp = kzalloc(sizeof(*vp),GFP_KERNEL);
	if (!vp) return vp;
	pvr2_channel_init(&vp->channel,mnp);
	pvr2_trace(PVR2_TRACE_STRUCT,"Creating pvr2_v4l2 id=%p",vp);

	vp->channel.check_func = pvr2_v4l2_internal_check;

	/* register streams */
	vp->dev_video = kzalloc(sizeof(*vp->dev_video),GFP_KERNEL);
	if (!vp->dev_video) goto fail;
	pvr2_v4l2_dev_init(vp->dev_video,vp,VFL_TYPE_GRABBER);
	if (pvr2_hdw_get_input_available(vp->channel.mc_head->hdw) &
	    (1 << PVR2_CVAL_INPUT_RADIO)) {
		vp->dev_radio = kzalloc(sizeof(*vp->dev_radio),GFP_KERNEL);
		if (!vp->dev_radio) goto fail;
		pvr2_v4l2_dev_init(vp->dev_radio,vp,VFL_TYPE_RADIO);
	}

	return vp;
 fail:
	pvr2_trace(PVR2_TRACE_STRUCT,"Failure creating pvr2_v4l2 id=%p",vp);
	pvr2_v4l2_destroy_no_lock(vp);
	return NULL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {struct pvr2_v4l2_fh* input_map; TYPE_6__ channel; struct pvr2_v4l2* vhead; TYPE_2__* vprev; TYPE_5__* vnext; int /*<<< orphan*/  prio; int /*<<< orphan*/ * rhp; } ;
struct TYPE_10__ {TYPE_3__* mc_head; } ;
struct pvr2_v4l2 {TYPE_5__* vfirst; TYPE_4__ channel; TYPE_2__* vlast; int /*<<< orphan*/  prio; } ;
struct pvr2_stream {int dummy; } ;
struct pvr2_hdw {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_11__ {TYPE_2__* vprev; } ;
struct TYPE_9__ {scalar_t__ disconnect_flag; } ;
struct TYPE_8__ {TYPE_5__* vnext; } ;
struct TYPE_7__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_OPEN_CLOSE ; 
 int /*<<< orphan*/  PVR2_TRACE_STRUCT ; 
 int /*<<< orphan*/  kfree (struct pvr2_v4l2_fh*) ; 
 int /*<<< orphan*/  pvr2_channel_done (TYPE_6__*) ; 
 int /*<<< orphan*/  pvr2_hdw_set_streaming (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_ioread_destroy (int /*<<< orphan*/ *) ; 
 struct pvr2_stream* pvr2_ioread_get_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_stream_set_callback (struct pvr2_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pvr2_v4l2_destroy_no_lock (struct pvr2_v4l2*) ; 
 int /*<<< orphan*/  v4l2_prio_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_v4l2_release(struct file *file)
{
	struct pvr2_v4l2_fh *fhp = file->private_data;
	struct pvr2_v4l2 *vp = fhp->vhead;
	struct pvr2_hdw *hdw = fhp->channel.mc_head->hdw;

	pvr2_trace(PVR2_TRACE_OPEN_CLOSE,"pvr2_v4l2_release");

	if (fhp->rhp) {
		struct pvr2_stream *sp;
		pvr2_hdw_set_streaming(hdw,0);
		sp = pvr2_ioread_get_stream(fhp->rhp);
		if (sp) pvr2_stream_set_callback(sp,NULL,NULL);
		pvr2_ioread_destroy(fhp->rhp);
		fhp->rhp = NULL;
	}

	v4l2_prio_close(&vp->prio, fhp->prio);
	file->private_data = NULL;

	if (fhp->vnext) {
		fhp->vnext->vprev = fhp->vprev;
	} else {
		vp->vlast = fhp->vprev;
	}
	if (fhp->vprev) {
		fhp->vprev->vnext = fhp->vnext;
	} else {
		vp->vfirst = fhp->vnext;
	}
	fhp->vnext = NULL;
	fhp->vprev = NULL;
	fhp->vhead = NULL;
	pvr2_channel_done(&fhp->channel);
	pvr2_trace(PVR2_TRACE_STRUCT,
		   "Destroying pvr_v4l2_fh id=%p",fhp);
	if (fhp->input_map) {
		kfree(fhp->input_map);
		fhp->input_map = NULL;
	}
	kfree(fhp);
	if (vp->channel.mc_head->disconnect_flag && !vp->vfirst) {
		pvr2_v4l2_destroy_no_lock(vp);
	}
	return 0;
}
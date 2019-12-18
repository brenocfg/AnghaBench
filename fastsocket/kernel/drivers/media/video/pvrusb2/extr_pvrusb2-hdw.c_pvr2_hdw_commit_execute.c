#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ext_controls {int count; int value; int /*<<< orphan*/  id; struct v4l2_ext_controls* controls; } ;
struct v4l2_ext_control {int count; int value; int /*<<< orphan*/  id; struct v4l2_ext_control* controls; } ;
struct TYPE_6__ {int video_gop_size; } ;
struct pvr2_hdw {int std_mask_cur; int res_ver_val; int res_ver_dirty; int state_pathway_ok; scalar_t__ input_val; scalar_t__ pathway_state; int res_hor_dirty; scalar_t__ cropw_val; scalar_t__ res_hor_val; int cropw_dirty; scalar_t__ croph_val; int croph_dirty; scalar_t__ active_stream_type; scalar_t__ desired_stream_type; int state_pipeline_pause; int srate_val; unsigned int control_cnt; int state_pipeline_config; scalar_t__ state_encoder_run; struct pvr2_ctrl* controls; scalar_t__ force_dirty; scalar_t__ tuner_updated; TYPE_1__* hdw_desc; TYPE_3__ enc_ctl_state; scalar_t__ srate_dirty; int /*<<< orphan*/  state_pipeline_idle; scalar_t__ input_dirty; scalar_t__ enc_unsafe_stale; scalar_t__ std_dirty; } ;
struct pvr2_ctrl {TYPE_2__* info; } ;
typedef  int /*<<< orphan*/  cs ;
typedef  int /*<<< orphan*/  c1 ;
struct TYPE_5__ {int /*<<< orphan*/  (* clear_dirty ) (struct pvr2_ctrl*) ;} ;
struct TYPE_4__ {scalar_t__ signal_routing_scheme; } ;

/* Variables and functions */
 scalar_t__ PVR2_CVAL_INPUT_DTV ; 
 scalar_t__ PVR2_CVAL_INPUT_RADIO ; 
 scalar_t__ PVR2_PATHWAY_ANALOG ; 
 scalar_t__ PVR2_PATHWAY_DIGITAL ; 
 scalar_t__ PVR2_ROUTING_SCHEME_GOTVIEW ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_GOP_SIZE ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  VIDIOC_S_EXT_CTRLS ; 
 int /*<<< orphan*/  cx2341x_ext_ctrls (TYPE_3__*,int /*<<< orphan*/ ,struct v4l2_ext_controls*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_ext_controls*,int /*<<< orphan*/ ,int) ; 
 void* min (int,scalar_t__) ; 
 scalar_t__ pvr2_encoder_adjust (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_hdw_gpio_chg_out (struct pvr2_hdw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_hdw_gpio_get_out (struct pvr2_hdw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_subdev_update (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  stub1 (struct pvr2_ctrl*) ; 
 int /*<<< orphan*/  trace_stbit (char*,int) ; 

__attribute__((used)) static int pvr2_hdw_commit_execute(struct pvr2_hdw *hdw)
{
	unsigned int idx;
	struct pvr2_ctrl *cptr;
	int disruptive_change;

	/* Handle some required side effects when the video standard is
	   changed.... */
	if (hdw->std_dirty) {
		int nvres;
		int gop_size;
		if (hdw->std_mask_cur & V4L2_STD_525_60) {
			nvres = 480;
			gop_size = 15;
		} else {
			nvres = 576;
			gop_size = 12;
		}
		/* Rewrite the vertical resolution to be appropriate to the
		   video standard that has been selected. */
		if (nvres != hdw->res_ver_val) {
			hdw->res_ver_val = nvres;
			hdw->res_ver_dirty = !0;
		}
		/* Rewrite the GOP size to be appropriate to the video
		   standard that has been selected. */
		if (gop_size != hdw->enc_ctl_state.video_gop_size) {
			struct v4l2_ext_controls cs;
			struct v4l2_ext_control c1;
			memset(&cs, 0, sizeof(cs));
			memset(&c1, 0, sizeof(c1));
			cs.controls = &c1;
			cs.count = 1;
			c1.id = V4L2_CID_MPEG_VIDEO_GOP_SIZE;
			c1.value = gop_size;
			cx2341x_ext_ctrls(&hdw->enc_ctl_state, 0, &cs,
					  VIDIOC_S_EXT_CTRLS);
		}
	}

	if (hdw->input_dirty && hdw->state_pathway_ok &&
	    (((hdw->input_val == PVR2_CVAL_INPUT_DTV) ?
	      PVR2_PATHWAY_DIGITAL : PVR2_PATHWAY_ANALOG) !=
	     hdw->pathway_state)) {
		/* Change of mode being asked for... */
		hdw->state_pathway_ok = 0;
		trace_stbit("state_pathway_ok",hdw->state_pathway_ok);
	}
	if (!hdw->state_pathway_ok) {
		/* Can't commit anything until pathway is ok. */
		return 0;
	}
	/* The broadcast decoder can only scale down, so if
	 * res_*_dirty && crop window < output format ==> enlarge crop.
	 *
	 * The mpeg encoder receives fields of res_hor_val dots and
	 * res_ver_val halflines.  Limits: hor<=720, ver<=576.
	 */
	if (hdw->res_hor_dirty && hdw->cropw_val < hdw->res_hor_val) {
		hdw->cropw_val = hdw->res_hor_val;
		hdw->cropw_dirty = !0;
	} else if (hdw->cropw_dirty) {
		hdw->res_hor_dirty = !0;           /* must rescale */
		hdw->res_hor_val = min(720, hdw->cropw_val);
	}
	if (hdw->res_ver_dirty && hdw->croph_val < hdw->res_ver_val) {
		hdw->croph_val = hdw->res_ver_val;
		hdw->croph_dirty = !0;
	} else if (hdw->croph_dirty) {
		int nvres = hdw->std_mask_cur & V4L2_STD_525_60 ? 480 : 576;
		hdw->res_ver_dirty = !0;
		hdw->res_ver_val = min(nvres, hdw->croph_val);
	}

	/* If any of the below has changed, then we can't do the update
	   while the pipeline is running.  Pipeline must be paused first
	   and decoder -> encoder connection be made quiescent before we
	   can proceed. */
	disruptive_change =
		(hdw->std_dirty ||
		 hdw->enc_unsafe_stale ||
		 hdw->srate_dirty ||
		 hdw->res_ver_dirty ||
		 hdw->res_hor_dirty ||
		 hdw->cropw_dirty ||
		 hdw->croph_dirty ||
		 hdw->input_dirty ||
		 (hdw->active_stream_type != hdw->desired_stream_type));
	if (disruptive_change && !hdw->state_pipeline_idle) {
		/* Pipeline is not idle; we can't proceed.  Arrange to
		   cause pipeline to stop so that we can try this again
		   later.... */
		hdw->state_pipeline_pause = !0;
		return 0;
	}

	if (hdw->srate_dirty) {
		/* Write new sample rate into control structure since
		 * the master copy is stale.  We must track srate
		 * separate from the mpeg control structure because
		 * other logic also uses this value. */
		struct v4l2_ext_controls cs;
		struct v4l2_ext_control c1;
		memset(&cs,0,sizeof(cs));
		memset(&c1,0,sizeof(c1));
		cs.controls = &c1;
		cs.count = 1;
		c1.id = V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ;
		c1.value = hdw->srate_val;
		cx2341x_ext_ctrls(&hdw->enc_ctl_state, 0, &cs,VIDIOC_S_EXT_CTRLS);
	}

	if (hdw->active_stream_type != hdw->desired_stream_type) {
		/* Handle any side effects of stream config here */
		hdw->active_stream_type = hdw->desired_stream_type;
	}

	if (hdw->hdw_desc->signal_routing_scheme ==
	    PVR2_ROUTING_SCHEME_GOTVIEW) {
		u32 b;
		/* Handle GOTVIEW audio switching */
		pvr2_hdw_gpio_get_out(hdw,&b);
		if (hdw->input_val == PVR2_CVAL_INPUT_RADIO) {
			/* Set GPIO 11 */
			pvr2_hdw_gpio_chg_out(hdw,(1 << 11),~0);
		} else {
			/* Clear GPIO 11 */
			pvr2_hdw_gpio_chg_out(hdw,(1 << 11),0);
		}
	}

	/* Check and update state for all sub-devices. */
	pvr2_subdev_update(hdw);

	hdw->tuner_updated = 0;
	hdw->force_dirty = 0;
	for (idx = 0; idx < hdw->control_cnt; idx++) {
		cptr = hdw->controls + idx;
		if (!cptr->info->clear_dirty) continue;
		cptr->info->clear_dirty(cptr);
	}

	if ((hdw->pathway_state == PVR2_PATHWAY_ANALOG) &&
	    hdw->state_encoder_run) {
		/* If encoder isn't running or it can't be touched, then
		   this will get worked out later when we start the
		   encoder. */
		if (pvr2_encoder_adjust(hdw) < 0) return !0;
	}

	hdw->state_pipeline_config = !0;
	/* Hardware state may have changed in a way to cause the cropping
	   capabilities to have changed.  So mark it stale, which will
	   cause a later re-fetch. */
	trace_stbit("state_pipeline_config",hdw->state_pipeline_config);
	return !0;
}
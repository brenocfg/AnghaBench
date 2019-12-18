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
struct pvr2_hdw {int enc_cur_valid; int /*<<< orphan*/  enc_ctl_state; int /*<<< orphan*/  enc_cur_state; } ;
struct cx2341x_mpeg_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int cx2341x_update (struct pvr2_hdw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pvr2_encoder_cmd ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,int) ; 

int pvr2_encoder_adjust(struct pvr2_hdw *hdw)
{
	int ret;
	ret = cx2341x_update(hdw,pvr2_encoder_cmd,
			     (hdw->enc_cur_valid ? &hdw->enc_cur_state : NULL),
			     &hdw->enc_ctl_state);
	if (ret) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Error from cx2341x module code=%d",ret);
	} else {
		memcpy(&hdw->enc_cur_state,&hdw->enc_ctl_state,
		       sizeof(struct cx2341x_mpeg_params));
		hdw->enc_cur_valid = !0;
	}
	return ret;
}
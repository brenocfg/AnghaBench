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
struct pvr2_hdw {scalar_t__ flag_ok; scalar_t__ vid_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  pvr2_hdw_state_sched (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_stream_setup (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace_stbit (char*,scalar_t__) ; 

void pvr2_hdw_render_useless(struct pvr2_hdw *hdw)
{
	if (!hdw->flag_ok) return;
	pvr2_trace(PVR2_TRACE_ERROR_LEGS,
		   "Device being rendered inoperable");
	if (hdw->vid_stream) {
		pvr2_stream_setup(hdw->vid_stream,NULL,0,0);
	}
	hdw->flag_ok = 0;
	trace_stbit("flag_ok",hdw->flag_ok);
	pvr2_hdw_state_sched(hdw);
}
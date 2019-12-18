#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct pvr2_hdw {int state_encoder_run; TYPE_1__ encoder_run_timer; int /*<<< orphan*/  state_encoder_runok; scalar_t__ state_encoder_ok; } ;

/* Variables and functions */
 int HZ ; 
 int TIME_MSEC_ENCODER_OK ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ pvr2_encoder_start (struct pvr2_hdw*) ; 
 scalar_t__ pvr2_encoder_stop (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  state_check_disable_encoder_run (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  state_check_enable_encoder_run (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  trace_stbit (char*,int) ; 

__attribute__((used)) static int state_eval_encoder_run(struct pvr2_hdw *hdw)
{
	if (hdw->state_encoder_run) {
		if (!state_check_disable_encoder_run(hdw)) return 0;
		if (hdw->state_encoder_ok) {
			del_timer_sync(&hdw->encoder_run_timer);
			if (pvr2_encoder_stop(hdw) < 0) return !0;
		}
		hdw->state_encoder_run = 0;
	} else {
		if (!state_check_enable_encoder_run(hdw)) return 0;
		if (pvr2_encoder_start(hdw) < 0) return !0;
		hdw->state_encoder_run = !0;
		if (!hdw->state_encoder_runok) {
			hdw->encoder_run_timer.expires =
				jiffies + (HZ * TIME_MSEC_ENCODER_OK / 1000);
			add_timer(&hdw->encoder_run_timer);
		}
	}
	trace_stbit("state_encoder_run",hdw->state_encoder_run);
	return !0;
}
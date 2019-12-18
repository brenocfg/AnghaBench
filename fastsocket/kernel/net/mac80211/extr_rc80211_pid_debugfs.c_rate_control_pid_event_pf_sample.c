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
union rc_pid_event_data {void* der_err; void* int_err; void* prop_err; void* pf_sample; } ;
struct rc_pid_event_buffer {int dummy; } ;
typedef  void* s32 ;

/* Variables and functions */
 int /*<<< orphan*/  RC_PID_EVENT_TYPE_PF_SAMPLE ; 
 int /*<<< orphan*/  rate_control_pid_event (struct rc_pid_event_buffer*,int /*<<< orphan*/ ,union rc_pid_event_data*) ; 

void rate_control_pid_event_pf_sample(struct rc_pid_event_buffer *buf,
					     s32 pf_sample, s32 prop_err,
					     s32 int_err, s32 der_err)
{
	union rc_pid_event_data evd;

	evd.pf_sample = pf_sample;
	evd.prop_err = prop_err;
	evd.int_err = int_err;
	evd.der_err = der_err;
	rate_control_pid_event(buf, RC_PID_EVENT_TYPE_PF_SAMPLE, &evd);
}
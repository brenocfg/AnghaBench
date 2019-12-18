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
union rc_pid_event_data {int index; int rate; } ;
struct rc_pid_event_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_PID_EVENT_TYPE_TX_RATE ; 
 int /*<<< orphan*/  rate_control_pid_event (struct rc_pid_event_buffer*,int /*<<< orphan*/ ,union rc_pid_event_data*) ; 

void rate_control_pid_event_tx_rate(struct rc_pid_event_buffer *buf,
					   int index, int rate)
{
	union rc_pid_event_data evd;

	evd.index = index;
	evd.rate = rate;
	rate_control_pid_event(buf, RC_PID_EVENT_TYPE_TX_RATE, &evd);
}
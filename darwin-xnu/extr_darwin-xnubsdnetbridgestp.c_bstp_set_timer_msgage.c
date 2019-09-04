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
struct bstp_port {scalar_t__ bp_port_msg_age; scalar_t__ bp_port_max_age; int bp_port_htime; int /*<<< orphan*/  bp_message_age_timer; } ;

/* Variables and functions */
 scalar_t__ BSTP_MESSAGE_AGE_INCR ; 
 int /*<<< orphan*/  bstp_timer_start (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
bstp_set_timer_msgage(struct bstp_port *bp)
{
	if (bp->bp_port_msg_age + BSTP_MESSAGE_AGE_INCR <=
	    bp->bp_port_max_age) {
		bstp_timer_start(&bp->bp_message_age_timer,
		    bp->bp_port_htime * 3);
	} else
		/* expires immediately */
		bstp_timer_start(&bp->bp_message_age_timer, 0);
}
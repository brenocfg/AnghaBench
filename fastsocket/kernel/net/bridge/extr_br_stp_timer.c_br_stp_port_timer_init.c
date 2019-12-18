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
struct net_bridge_port {int /*<<< orphan*/  hold_timer; int /*<<< orphan*/  forward_delay_timer; int /*<<< orphan*/  message_age_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_forward_delay_timer_expired ; 
 int /*<<< orphan*/  br_hold_timer_expired ; 
 int /*<<< orphan*/  br_message_age_timer_expired ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void br_stp_port_timer_init(struct net_bridge_port *p)
{
	setup_timer(&p->message_age_timer, br_message_age_timer_expired,
		      (unsigned long) p);

	setup_timer(&p->forward_delay_timer, br_forward_delay_timer_expired,
		      (unsigned long) p);

	setup_timer(&p->hold_timer, br_hold_timer_expired,
		      (unsigned long) p);
}
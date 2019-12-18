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
struct musb {scalar_t__ a_wait_bcon; } ;

/* Variables and functions */
 scalar_t__ TIMER_DELAY ; 
 scalar_t__ is_host_enabled (struct musb*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  musb_conn_timer ; 

void musb_platform_enable(struct musb *musb)
{
	if (is_host_enabled(musb)) {
		mod_timer(&musb_conn_timer, jiffies + TIMER_DELAY);
		musb->a_wait_bcon = TIMER_DELAY;
	}
}
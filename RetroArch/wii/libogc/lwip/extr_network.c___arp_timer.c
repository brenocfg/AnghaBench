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

/* Variables and functions */
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchunnest () ; 
 int /*<<< orphan*/  __lwp_wd_insert_ticks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arp_time_cntrl ; 
 scalar_t__ etharp_tmr ; 
 int /*<<< orphan*/  net_arp_ticks ; 
 int /*<<< orphan*/  net_callback (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tmr_callback ; 

__attribute__((used)) static void __arp_timer(void *arg)
{
	__lwp_thread_dispatchdisable();
	net_callback(tmr_callback,(void*)etharp_tmr);
	__lwp_wd_insert_ticks(&arp_time_cntrl,net_arp_ticks);
	__lwp_thread_dispatchunnest();
}
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
 scalar_t__ dhcp_fine_tmr ; 
 int /*<<< orphan*/  dhcp_finetimer_cntrl ; 
 int /*<<< orphan*/  net_callback (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  net_dhcpfine_ticks ; 
 int /*<<< orphan*/  tmr_callback ; 

__attribute__((used)) static void __dhcpfine_timer(void *arg)
{
	__lwp_thread_dispatchdisable();
	net_callback(tmr_callback,(void*)dhcp_fine_tmr);
	__lwp_wd_insert_ticks(&dhcp_finetimer_cntrl,net_dhcpfine_ticks);
	__lwp_thread_dispatchunnest();
}
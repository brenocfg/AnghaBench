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
 int /*<<< orphan*/  net_callback (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  net_tcp_ticks ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__,scalar_t__) ; 
 scalar_t__ tcp_active_pcbs ; 
 int tcp_timer_active ; 
 int /*<<< orphan*/  tcp_timer_cntrl ; 
 scalar_t__ tcp_tmr ; 
 scalar_t__ tcp_tw_pcbs ; 
 int /*<<< orphan*/  tmr_callback ; 

__attribute__((used)) static void __tcp_timer(void *arg)
{
#ifdef _NET_DEBUG
	printf("__tcp_timer(%d,%p,%p)\n",tcp_timer_active,tcp_active_pcbs,tcp_tw_pcbs);
#endif
	__lwp_thread_dispatchdisable();
	net_callback(tmr_callback,(void*)tcp_tmr);
	if (tcp_active_pcbs || tcp_tw_pcbs) {
		__lwp_wd_insert_ticks(&tcp_timer_cntrl,net_tcp_ticks);
	} else
		tcp_timer_active = 0;
	__lwp_thread_dispatchunnest();
}
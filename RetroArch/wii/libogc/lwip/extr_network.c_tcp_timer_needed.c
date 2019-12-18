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
 int /*<<< orphan*/  __lwp_wd_insert_ticks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_tcp_ticks ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ tcp_active_pcbs ; 
 int tcp_timer_active ; 
 int /*<<< orphan*/  tcp_timer_cntrl ; 
 scalar_t__ tcp_tw_pcbs ; 

void tcp_timer_needed(void)
{
#ifdef _NET_DEBUG
	printf("tcp_timer_needed()\n");
#endif
	if(!tcp_timer_active && (tcp_active_pcbs || tcp_tw_pcbs)) {
		tcp_timer_active = 1;
		__lwp_wd_insert_ticks(&tcp_timer_cntrl,net_tcp_ticks);
	}
}
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
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ lro_timer_set ; 
 int /*<<< orphan*/  tcp_lro_flush_flows () ; 
 int /*<<< orphan*/  tcp_lro_lock ; 

__attribute__((used)) static void
tcp_lro_timer_proc(void *arg1, void *arg2)
{
#pragma unused(arg1, arg2)

	lck_mtx_lock_spin(&tcp_lro_lock);
	lro_timer_set = 0;
	lck_mtx_unlock(&tcp_lro_lock);
	tcp_lro_flush_flows();
}
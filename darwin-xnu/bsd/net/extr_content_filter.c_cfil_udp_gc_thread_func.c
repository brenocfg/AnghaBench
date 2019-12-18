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
typedef  int /*<<< orphan*/  wait_result_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ cfil_info_udp_expire ; 
 scalar_t__ cfil_udp_gc_thread ; 
 int /*<<< orphan*/  cfil_udp_gc_thread_sleep (int) ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  thread_block_parameter (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_set_thread_name (scalar_t__,char*) ; 

__attribute__((used)) static void
cfil_udp_gc_thread_func(void *v, wait_result_t w)
{
#pragma unused(v, w)

	ASSERT(cfil_udp_gc_thread == current_thread());
	thread_set_thread_name(current_thread(), "CFIL_UPD_GC");

	// Kick off gc shortly
	cfil_udp_gc_thread_sleep(false);
	thread_block_parameter((thread_continue_t) cfil_info_udp_expire, NULL);
	/* NOTREACHED */
}
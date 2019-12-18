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
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ ml_recent_wake () ; 
 scalar_t__ mp_recent_debugger_activity () ; 
 scalar_t__ panic_active () ; 
 scalar_t__ pmap_tlb_flush_timeout ; 
 scalar_t__ spinlock_timed_out ; 

boolean_t machine_timeout_suspended(void) {
	return (pmap_tlb_flush_timeout || spinlock_timed_out || panic_active() || mp_recent_debugger_activity() || ml_recent_wake());
}
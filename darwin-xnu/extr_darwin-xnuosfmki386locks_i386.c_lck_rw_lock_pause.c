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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_pause () ; 
 int /*<<< orphan*/  handle_pending_TLB_flushes () ; 

__attribute__((used)) static inline void
lck_rw_lock_pause(boolean_t interrupts_enabled)
{
	if (!interrupts_enabled)
		handle_pending_TLB_flushes();
	cpu_pause();
}
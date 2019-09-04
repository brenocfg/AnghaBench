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
typedef  int /*<<< orphan*/  usimple_lock_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_pause () ; 
 int /*<<< orphan*/  handle_pending_TLB_flushes () ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  simple_lock_try (int /*<<< orphan*/ ) ; 

void
usimple_lock_try_lock_loop(usimple_lock_t l)
{
	boolean_t istate = ml_get_interrupts_enabled();
	while (!simple_lock_try((l))) {
		if (!istate)
			handle_pending_TLB_flushes();
		cpu_pause();
	}
}
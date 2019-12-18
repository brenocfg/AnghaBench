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
typedef  int /*<<< orphan*/  x86_saved_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PANIC_MACHINE_CHECK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  panic_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void

panic_machine_check64(x86_saved_state_t *sp)
{
	panic_64(sp, PANIC_MACHINE_CHECK, "Machine Check", TRUE);

}
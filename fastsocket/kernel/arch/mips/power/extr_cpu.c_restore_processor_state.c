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
 scalar_t__ cpu_has_dsp ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ is_fpu_owner () ; 
 int /*<<< orphan*/  restore_dsp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saved_status ; 
 int /*<<< orphan*/  write_c0_status (int /*<<< orphan*/ ) ; 

void restore_processor_state(void)
{
	write_c0_status(saved_status);

	if (is_fpu_owner())
		restore_fp(current);
	if (cpu_has_dsp)
		restore_dsp(current);
}
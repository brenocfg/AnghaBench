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
 int /*<<< orphan*/  read_c0_status () ; 
 int /*<<< orphan*/  save_dsp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saved_status ; 

void save_processor_state(void)
{
	saved_status = read_c0_status();

	if (is_fpu_owner())
		save_fp(current);
	if (cpu_has_dsp)
		save_dsp(current);
}
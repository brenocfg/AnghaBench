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
 int /*<<< orphan*/  GET_CYCLES () ; 
 int /*<<< orphan*/  SET_CYCLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_initial_cycles ; 

void m68k_end_timeslice(void)
{
	m68ki_initial_cycles = GET_CYCLES();
	SET_CYCLES(0);
}
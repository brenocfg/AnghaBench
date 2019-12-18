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
 int GET_CYCLES () ; 
 int m68ki_initial_cycles ; 

int m68k_cycles_run(void)
{
	return m68ki_initial_cycles - GET_CYCLES();
}
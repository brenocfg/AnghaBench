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
 unsigned int CCNT ; 
 int PMCR_E ; 
 unsigned int PMN0 ; 
 int arm11_read_pmnc () ; 
 int /*<<< orphan*/  arm11_reset_counter (unsigned int) ; 
 int /*<<< orphan*/  arm11_write_pmnc (int) ; 

int arm11_stop_pmu(void)
{
	unsigned int cnt;

	arm11_write_pmnc(arm11_read_pmnc() & ~PMCR_E);

	for (cnt = PMN0; cnt <= CCNT; cnt++)
		arm11_reset_counter(cnt);

	return 0;
}
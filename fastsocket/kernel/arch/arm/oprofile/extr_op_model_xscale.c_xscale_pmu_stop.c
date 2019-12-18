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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PMU_ENABLE ; 
 int /*<<< orphan*/  XSCALE_PMU_IRQ ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pmnc () ; 
 int /*<<< orphan*/  results ; 
 int /*<<< orphan*/  write_pmnc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xscale_pmu_stop(void)
{
	u32 pmnc = read_pmnc();

	pmnc &= ~PMU_ENABLE;
	write_pmnc(pmnc);

	free_irq(XSCALE_PMU_IRQ, results);
}
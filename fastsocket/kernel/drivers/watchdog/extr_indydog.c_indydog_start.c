#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int cpuctrl0; } ;

/* Variables and functions */
 int SGIMC_CCTRL0_WDOG ; 
 int /*<<< orphan*/  indydog_lock ; 
 TYPE_1__* sgimc ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void indydog_start(void)
{
	u32 mc_ctrl0;

	spin_lock(&indydog_lock);
	mc_ctrl0 = sgimc->cpuctrl0;
	mc_ctrl0 = sgimc->cpuctrl0 | SGIMC_CCTRL0_WDOG;
	sgimc->cpuctrl0 = mc_ctrl0;
	spin_unlock(&indydog_lock);
}
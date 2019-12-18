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
 int PMC_INIT ; 
 int /*<<< orphan*/  measurement_alert_subclass_register () ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  setup_pmc_cpu ; 

__attribute__((used)) static int reserve_pmc_hardware(void)
{
	int flags = PMC_INIT;

	on_each_cpu(setup_pmc_cpu, &flags, 1);
	measurement_alert_subclass_register();

	return 0;
}
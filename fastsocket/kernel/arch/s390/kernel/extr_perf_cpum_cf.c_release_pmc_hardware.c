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
 int PMC_RELEASE ; 
 int /*<<< orphan*/  measurement_alert_subclass_unregister () ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  setup_pmc_cpu ; 

__attribute__((used)) static void release_pmc_hardware(void)
{
	int flags = PMC_RELEASE;

	on_each_cpu(setup_pmc_cpu, &flags, 1);
	measurement_alert_subclass_unregister();
}
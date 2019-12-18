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
 int /*<<< orphan*/  boot_cpu_physical_apicid ; 
 int /*<<< orphan*/  read_apic_id () ; 

__attribute__((used)) static int es7000_check_phys_apicid_present(int cpu_physical_apicid)
{
	boot_cpu_physical_apicid = read_apic_id();
	return 1;
}
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
 int /*<<< orphan*/  clear_APIC_ibs () ; 
 scalar_t__ ibs_caps ; 

__attribute__((used)) static void op_amd_cpu_shutdown(void)
{
	if (ibs_caps)
		clear_APIC_ibs();
}
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
 int /*<<< orphan*/  mpic_teardown_this_cpu (int) ; 
 int /*<<< orphan*/  pseries_kexec_cpu_down (int,int) ; 

__attribute__((used)) static void pseries_kexec_cpu_down_mpic(int crash_shutdown, int secondary)
{
	pseries_kexec_cpu_down(crash_shutdown, secondary);
	mpic_teardown_this_cpu(secondary);
}
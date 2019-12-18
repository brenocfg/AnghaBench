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
 int /*<<< orphan*/  octeon_hal_setup_per_cpu_reserved32 ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void octeon_hal_setup_reserved32(void)
{
#ifdef CONFIG_CAVIUM_RESERVE32_USE_WIRED_TLB
	on_each_cpu(octeon_hal_setup_per_cpu_reserved32, NULL, 0, 1);
#endif
}
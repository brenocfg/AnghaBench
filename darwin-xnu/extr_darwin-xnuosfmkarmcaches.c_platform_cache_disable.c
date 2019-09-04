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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTLR_DCACHE ; 

void
platform_cache_disable(void)
{
#if (__ARM_ARCH__ < 8)
	uint32_t sctlr_value = 0;

	/* Disable dcache allocation. */
	__asm__ volatile("mrc p15, 0, %0, c1, c0, 0"
	                 : "=r"(sctlr_value));

	sctlr_value &= ~SCTLR_DCACHE;

	__asm__ volatile("mcr p15, 0, %0, c1, c0, 0\n"
	                 "isb"
	                 :: "r"(sctlr_value));
#endif /* (__ARM_ARCH__ < 8) */
}
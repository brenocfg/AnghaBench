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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __builtin_arm_mrc (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

uint32_t
machine_read_clidr(void)
{
#if __arm__
	uint32_t clidr = __builtin_arm_mrc(15,1,0,0,1);
#else
	uint64_t clidr;
	__asm__ volatile("mrs	%0, CLIDR_EL1" : "=r" (clidr));
#endif
	return (uint32_t)clidr;
}
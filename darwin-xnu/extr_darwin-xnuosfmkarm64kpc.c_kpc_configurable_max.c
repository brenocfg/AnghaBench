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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 unsigned long long KPC_ARM64_COUNTER_WIDTH ; 

uint64_t
kpc_configurable_max(void)
{
	return (1ULL << KPC_ARM64_COUNTER_WIDTH) - 1;
}
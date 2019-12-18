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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int PAGE_SHIFT ; 

__attribute__((used)) static inline unsigned long deap_pfn(u8 edeap, u32 deap)
{
	deap >>= PAGE_SHIFT;
	deap |= (edeap & 1) << (32 - PAGE_SHIFT);
	return deap;
}
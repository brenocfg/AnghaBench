#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ PMU_XSC1 ; 
 TYPE_1__* pmu ; 

__attribute__((used)) static u32 read_pmnc(void)
{
	u32 val;

	if (pmu->id == PMU_XSC1)
		__asm__ __volatile__ ("mrc p14, 0, %0, c0, c0, 0" : "=r" (val));
	else {
		__asm__ __volatile__ ("mrc p14, 0, %0, c0, c1, 0" : "=r" (val));
		/* bits 1-2 and 4-23 are read-unpredictable */
		val &= 0xff000009;
	}

	return val;
}
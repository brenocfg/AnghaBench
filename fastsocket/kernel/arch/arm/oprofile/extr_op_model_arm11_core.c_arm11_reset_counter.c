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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ count; } ;

/* Variables and functions */
#define  CCNT 130 
 size_t CPU_COUNTER (int /*<<< orphan*/ ,unsigned int) ; 
#define  PMN0 129 
#define  PMN1 128 
 TYPE_1__* counter_config ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void arm11_reset_counter(unsigned int cnt)
{
	u32 val = -(u32)counter_config[CPU_COUNTER(smp_processor_id(), cnt)].count;
	switch (cnt) {
	case CCNT:
		asm volatile("mcr p15, 0, %0, c15, c12, 1" : : "r" (val));
		break;

	case PMN0:
		asm volatile("mcr p15, 0, %0, c15, c12, 2" : : "r" (val));
		break;

	case PMN1:
		asm volatile("mcr p15, 0, %0, c15, c12, 3" : : "r" (val));
		break;
	}
}
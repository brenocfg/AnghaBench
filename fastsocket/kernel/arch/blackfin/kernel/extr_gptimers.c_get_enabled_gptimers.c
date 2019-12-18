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
typedef  int uint16_t ;
struct TYPE_2__ {int enable; } ;

/* Variables and functions */
 int BFIN_TIMER_NUM_GROUP ; 
 TYPE_1__** group_regs ; 

uint16_t get_enabled_gptimers(void)
{
	int i;
	uint16_t result = 0;
	for (i = 0; i < BFIN_TIMER_NUM_GROUP; ++i)
		result |= (group_regs[i]->enable << (i << 3));
	return result;
}
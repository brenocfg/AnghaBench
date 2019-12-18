#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ counter_bias; } ;
typedef  TYPE_1__ syssram ;

/* Variables and functions */
 scalar_t__ CONF_GetCounterBias (int*) ; 
 int TB_TIMER_CLOCK ; 
 int /*<<< orphan*/  __SYS_GetRTC (int*) ; 
 TYPE_1__* __SYS_LockSram () ; 
 int /*<<< orphan*/  __SYS_UnlockSram (int /*<<< orphan*/ ) ; 

u64 SYS_Time()
{
	u64 current_time = 0;
    u32 gmtime =0;
    __SYS_GetRTC(&gmtime);
    current_time = gmtime;
#ifdef HW_RVL
	u32 bias;
	if (CONF_GetCounterBias(&bias) >= 0)
		current_time += bias;
#else
	syssram* sram = __SYS_LockSram();
	current_time += sram->counter_bias;
	__SYS_UnlockSram(0);
#endif
	return (TB_TIMER_CLOCK * 1000) * current_time;
}
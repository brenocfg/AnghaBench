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
typedef  int u32 ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CARDIO_OP_TIMEDOUT ; 
 int TB_TIMER_CLOCK ; 
 int /*<<< orphan*/ * _ioError ; 
 int gettick () ; 

__attribute__((used)) static u32 __card_checktimeout(s32 drv_no,u32 startT,u32 timeout)
{
	u32 endT,diff;
	u32 msec;

	endT = gettick();
	if(endT<startT) {
		diff = (endT+(-1-startT))+1;
	} else
		diff = (endT-startT);

	msec = (diff/TB_TIMER_CLOCK);
	if(msec<=timeout) return 0;

	_ioError[drv_no] |= CARDIO_OP_TIMEDOUT;
	return 1;
}
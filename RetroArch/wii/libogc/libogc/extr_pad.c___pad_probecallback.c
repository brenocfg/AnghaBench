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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_ENABLEDMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pad_doreset () ; 
 int /*<<< orphan*/  __pad_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pad_resettingchan ; 
 int /*<<< orphan*/  __pad_waitingbits ; 

__attribute__((used)) static void __pad_probecallback(s32 chan,u32 type)
{
	if(!(type&0x0f)) {
		__pad_enable(__pad_resettingchan);
		__pad_waitingbits |= PAD_ENABLEDMASK(__pad_resettingchan);
	}
	__pad_doreset();
}
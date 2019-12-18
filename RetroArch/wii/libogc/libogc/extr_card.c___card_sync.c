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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t s32 ;
struct TYPE_3__ {int /*<<< orphan*/  wait_sync_queue; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_BUSY ; 
 size_t CARD_GetErrorCode (size_t) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 TYPE_1__* cardmap ; 

__attribute__((used)) static s32 __card_sync(s32 chn)
{
	s32 ret;
	u32 level;
	card_block *card = &cardmap[chn];

	_CPU_ISR_Disable(level);
	while((ret=CARD_GetErrorCode(chn))==CARD_ERROR_BUSY) {
		LWP_ThreadSleep(card->wait_sync_queue);
	}
	_CPU_ISR_Restore(level);
	return ret;
}
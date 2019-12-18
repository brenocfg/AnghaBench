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
struct TYPE_3__ {size_t result; int /*<<< orphan*/  timeout_svc; scalar_t__ mount_step; scalar_t__ attached; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  EXI_Detach (size_t) ; 
 int /*<<< orphan*/  EXI_RegisterEXICallback (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_CancelAlarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 TYPE_1__* cardmap ; 

__attribute__((used)) static void __card_dounmount(s32 chn,s32 result)
{
	u32 level;
	card_block *card;

	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return;
	card = &cardmap[chn];

	_CPU_ISR_Disable(level);
	if(card->attached) {
		card->attached = 0;
		card->mount_step = 0;
		card->result = result;
		EXI_RegisterEXICallback(chn,NULL);
		EXI_Detach(chn);
		SYS_CancelAlarm(card->timeout_svc);
	}
	_CPU_ISR_Restore(level);
}
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
typedef  void* cardcallback ;
struct TYPE_3__ {scalar_t__ result; int attached; int /*<<< orphan*/ * card_unlock_cb; int /*<<< orphan*/ * curr_fat; int /*<<< orphan*/ * curr_dir; int /*<<< orphan*/  timeout_svc; scalar_t__ mount_step; int /*<<< orphan*/ * card_exi_cb; void* card_api_cb; void* card_ext_cb; void* workarea; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_BUSY ; 
 size_t CARD_ERROR_FATAL_ERROR ; 
 size_t CARD_ERROR_NOCARD ; 
 size_t CARD_ERROR_READY ; 
 size_t CARD_ERROR_WRONGDEVICE ; 
 scalar_t__ EXI_Attach (size_t,int /*<<< orphan*/ ) ; 
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 int EXI_FLAG_ATTACH ; 
 int EXI_GetState (size_t) ; 
 scalar_t__ EXI_Lock (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXI_RegisterEXICallback (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_CancelAlarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 void* __card_defaultapicallback ; 
 int /*<<< orphan*/  __card_domount (size_t) ; 
 int /*<<< orphan*/  __card_exthandler ; 
 int /*<<< orphan*/ * __card_mountcallback ; 
 int /*<<< orphan*/  __card_unlockedhandler ; 
 TYPE_1__* cardmap ; 

s32 CARD_MountAsync(s32 chn,void *workarea,cardcallback detach_cb,cardcallback attach_cb)
{
	s32 ret = CARD_ERROR_READY;
	u32 level;
	cardcallback attachcb = NULL;
	card_block *card = NULL;
	if(!workarea) return CARD_ERROR_NOCARD;
	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_FATAL_ERROR;
	card = &cardmap[chn];

	_CPU_ISR_Disable(level);
	if(card->result==CARD_ERROR_BUSY) {
		_CPU_ISR_Restore(level);
		return CARD_ERROR_BUSY;
	}
	if(card->attached || !(EXI_GetState(chn)&EXI_FLAG_ATTACH)) {
		card->result = CARD_ERROR_BUSY;
		card->workarea = workarea;
		card->card_ext_cb = detach_cb;

		attachcb = attach_cb;
		if(!attachcb) attachcb = __card_defaultapicallback;
		card->card_api_cb = attachcb;
		card->card_exi_cb = NULL;

		if(!card->attached) {
			if(EXI_Attach(chn,__card_exthandler)==0) {
				card->result = CARD_ERROR_NOCARD;
				_CPU_ISR_Restore(level);
				return CARD_ERROR_NOCARD;
			}
		}
		card->mount_step = 0;
		card->attached = 1;
		EXI_RegisterEXICallback(chn,NULL);
		SYS_CancelAlarm(card->timeout_svc);
		card->curr_dir = NULL;
		card->curr_fat = NULL;
		_CPU_ISR_Restore(level);

		card->card_unlock_cb = __card_mountcallback;
		if(EXI_Lock(chn,EXI_DEVICE_0,__card_unlockedhandler)==0) return 0;

		card->card_unlock_cb = NULL;
		__card_domount(chn);
		return 1;
	}

	ret = CARD_ERROR_WRONGDEVICE;
	_CPU_ISR_Restore(level);
	return ret;
}
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
typedef  int u32 ;
typedef  size_t s32 ;
struct TYPE_3__ {int mount_step; size_t card_size; size_t sector_size; scalar_t__ attached; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_BUSY ; 
 size_t CARD_ERROR_FATAL_ERROR ; 
 size_t CARD_ERROR_NOCARD ; 
 size_t CARD_ERROR_READY ; 
 size_t CARD_ERROR_WRONGDEVICE ; 
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 int EXI_FLAG_ATTACH ; 
 scalar_t__ EXI_GetID (size_t,int /*<<< orphan*/ ,int*) ; 
 int EXI_GetState (size_t) ; 
 size_t EXI_ProbeEx (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int _ROTL (int,int) ; 
 int /*<<< orphan*/  __card_iscard (int) ; 
 size_t* card_sector_size ; 
 TYPE_1__* cardmap ; 

s32 CARD_ProbeEx(s32 chn,s32 *mem_size,s32 *sect_size)
{
	s32 ret;
	u32 level,card_id;
	card_block *card = NULL;
	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_FATAL_ERROR;
	card = &cardmap[chn];

	_CPU_ISR_Disable(level);
	ret = EXI_ProbeEx(chn);
	if(ret<=0) {
		if(!ret) ret = CARD_ERROR_BUSY;
		else ret = CARD_ERROR_NOCARD;
		_CPU_ISR_Restore(level);
		return ret;
	}

	if(card->attached) {
		if(card->mount_step<1) {
			_CPU_ISR_Restore(level);
			return CARD_ERROR_BUSY;
		}
		if(mem_size) *mem_size = card->card_size;
		if(sect_size) *sect_size = card->sector_size;

		_CPU_ISR_Restore(level);
		return CARD_ERROR_READY;
	}

	if(EXI_GetState(chn)&EXI_FLAG_ATTACH) ret = CARD_ERROR_WRONGDEVICE;
	else {
		ret = CARD_ERROR_BUSY;
		if(EXI_GetID(chn,EXI_DEVICE_0,&card_id)) {
			if(!__card_iscard(card_id)) ret = CARD_ERROR_WRONGDEVICE;
			else {
				if(mem_size) *mem_size = card_id&0xFC;
				if(sect_size) {
					u32 idx = _ROTL(card_id,23)&0x1c;
					*sect_size = card_sector_size[idx>>2];
				}
				ret = CARD_ERROR_READY;
			}
		}
	}

	_CPU_ISR_Restore(level);
	return ret;
}
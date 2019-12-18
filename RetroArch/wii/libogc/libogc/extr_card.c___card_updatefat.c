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
typedef  int /*<<< orphan*/  u16 ;
struct card_bat {int /*<<< orphan*/  chksum2; int /*<<< orphan*/  chksum1; int /*<<< orphan*/  updated; } ;
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  cardcallback ;
struct TYPE_3__ {int sector_size; scalar_t__ workarea; int /*<<< orphan*/  card_erase_cb; int /*<<< orphan*/  attached; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_FATAL_ERROR ; 
 size_t CARD_ERROR_NOCARD ; 
 int /*<<< orphan*/  DCStoreRange (struct card_bat*,int) ; 
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  __card_checksum (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __card_faterasecallback ; 
 size_t __card_sectorerase (size_t,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* cardmap ; 

__attribute__((used)) static s32 __card_updatefat(s32 chn,struct card_bat *fatblock,cardcallback callback)
{
	card_block *card = NULL;
	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_FATAL_ERROR;
	card = &cardmap[chn];

	if(!card->attached) return CARD_ERROR_NOCARD;

	++fatblock->updated;
	__card_checksum((u16*)(((u32)fatblock)+4),0x1ffc,&fatblock->chksum1,&fatblock->chksum2);
	DCStoreRange(fatblock,8192);
	card->card_erase_cb = callback;

	return __card_sectorerase(chn,(((u32)fatblock-(u32)card->workarea)>>13)*card->sector_size,__card_faterasecallback);
}
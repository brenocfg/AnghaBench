#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  (* cardcallback ) (size_t,size_t) ;
struct TYPE_4__ {int format_step; int sector_size; int /*<<< orphan*/  (* card_api_cb ) (size_t,size_t) ;scalar_t__ workarea; scalar_t__ curr_fat; scalar_t__ curr_dir; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 int CARD_SYSAREA ; 
 scalar_t__ CARD_SYSBAT ; 
 scalar_t__ CARD_SYSBAT_BACK ; 
 scalar_t__ CARD_SYSDIR ; 
 scalar_t__ CARD_SYSDIR_BACK ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_1__*,size_t) ; 
 size_t __card_sectorerase (size_t,int,void (*) (size_t,size_t)) ; 
 size_t __card_write (size_t,int,int,scalar_t__,void (*) (size_t,size_t)) ; 
 TYPE_1__* cardmap ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void __format_callback(s32 chn,s32 result)
{
	s32 ret;
	cardcallback cb = NULL;
	card_block *card = &cardmap[chn];

	ret = result;
	if(ret>=0) {
		if((++card->format_step)<CARD_SYSAREA) {
			if((ret=__card_sectorerase(chn,(card->format_step*card->sector_size),__format_callback))>=0) return;
			goto exit;
		}
		if(card->format_step<10) {
			if((ret=__card_write(chn,((card->format_step-CARD_SYSAREA)*card->sector_size),8192,card->workarea+((card->format_step-CARD_SYSAREA)<<13),__format_callback))>=0) return;
			goto exit;
		}

		card->curr_dir = card->workarea+CARD_SYSDIR;
		memcpy(card->curr_dir,card->workarea+CARD_SYSDIR_BACK,8192);

		card->curr_fat = card->workarea+CARD_SYSBAT;
		memcpy(card->curr_fat,card->workarea+CARD_SYSBAT_BACK,8192);
	}
exit:
	cb = card->card_api_cb;
	card->card_api_cb = NULL;
	__card_putcntrlblock(card,ret);
	if(cb) cb(chn,ret);
}
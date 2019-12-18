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
struct TYPE_4__ {scalar_t__ cmd_blck_cnt; int /*<<< orphan*/  (* card_xfer_cb ) (size_t,size_t) ;int /*<<< orphan*/  card_api_cb; int /*<<< orphan*/  cmd_usr_buf; int /*<<< orphan*/  cmd_sector_addr; int /*<<< orphan*/  transfer_cnt; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_READY ; 
 scalar_t__ CARD_READSIZE ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_1__*,size_t) ; 
 size_t __card_readsegment (size_t,void (*) (size_t,size_t)) ; 
 TYPE_1__* cardmap ; 

__attribute__((used)) static void __blockreadcallback(s32 chn,s32 result)
{
	s32 ret = CARD_ERROR_READY;
	cardcallback cb = NULL;
	card_block *card = &cardmap[chn];
	ret = result;
	if(ret>=0) {
		card->transfer_cnt += CARD_READSIZE;
		card->cmd_sector_addr += CARD_READSIZE;
		card->cmd_usr_buf += CARD_READSIZE;
		if((--card->cmd_blck_cnt)>0) {
			if((ret=__card_readsegment(chn,__blockreadcallback))>=CARD_ERROR_READY) return;
		}
	}

	if(!card->card_api_cb) __card_putcntrlblock(card,ret);
	cb = card->card_xfer_cb;
	if(cb) {
		card->card_xfer_cb = NULL;
		cb(chn,ret);
	}
}
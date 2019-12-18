#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct card_dat {int dummy; } ;
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  (* cardcallback ) (size_t,size_t) ;
struct TYPE_5__ {int sector_size; int /*<<< orphan*/  (* card_erase_cb ) (size_t,size_t) ;int /*<<< orphan*/  card_api_cb; scalar_t__ workarea; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 int /*<<< orphan*/  __card_dirwritecallback ; 
 struct card_dat* __card_getdirblock (TYPE_1__*) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_1__*,size_t) ; 
 size_t __card_write (size_t,int,int,struct card_dat*,int /*<<< orphan*/ ) ; 
 TYPE_1__* cardmap ; 

__attribute__((used)) static void __card_direrasecallback(s32 chn,s32 result)
{
	s32 ret;
	cardcallback cb = NULL;
	struct card_dat *dirblock = NULL;
	card_block *card = &cardmap[chn];
	ret = result;
	if(ret>=0) {
		dirblock = __card_getdirblock(card);
		if((ret=__card_write(chn,(((u32)dirblock-(u32)card->workarea)>>13)*card->sector_size,8192,dirblock,__card_dirwritecallback))>=0) return;
	}
	if(!card->card_api_cb) __card_putcntrlblock(card,ret);

	cb = card->card_erase_cb;
	if(cb) {
		card->card_erase_cb = NULL;
		cb(chn,ret);
	}
}
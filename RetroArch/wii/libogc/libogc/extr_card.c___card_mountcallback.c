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
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  (* cardcallback ) (size_t,size_t) ;
struct TYPE_5__ {int mount_step; int /*<<< orphan*/  (* card_api_cb ) (size_t,size_t) ;} ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_IOERROR ; 
 size_t CARD_ERROR_NOCARD ; 
 size_t CARD_ERROR_UNLOCKED ; 
 size_t __card_domount (size_t) ; 
 int /*<<< orphan*/  __card_dounmount (size_t,size_t) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_1__*,size_t) ; 
 size_t __card_verify (TYPE_1__*) ; 
 TYPE_1__* cardmap ; 

__attribute__((used)) static void __card_mountcallback(s32 chn,s32 result)
{
	s32 ret;
	cardcallback cb;
	card_block *card = &cardmap[chn];

	ret = result;
	if(ret==CARD_ERROR_NOCARD || ret==CARD_ERROR_IOERROR) {
		__card_dounmount(chn,ret);
		__card_putcntrlblock(card,ret);
	}else if(ret==CARD_ERROR_UNLOCKED) {
		if((ret=__card_domount(chn))>=0) return;
	} else {
		if((++card->mount_step)<7) {
			if((ret=__card_domount(chn))>=0) return;
		} else {
			ret = __card_verify(card);
			__card_putcntrlblock(card,ret);
		}
	}

	cb = card->card_api_cb;
	card->card_api_cb = NULL;
	if(cb) cb(chn,ret);
}
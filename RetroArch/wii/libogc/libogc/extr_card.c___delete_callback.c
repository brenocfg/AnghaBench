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
struct TYPE_4__ {int /*<<< orphan*/  curr_fileblock; int /*<<< orphan*/  (* card_api_cb ) (size_t,size_t) ;} ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t __card_freeblock (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (size_t,size_t)) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_1__*,size_t) ; 
 TYPE_1__* cardmap ; 

__attribute__((used)) static void __delete_callback(s32 chn,s32 result)
{
	s32 ret;
	cardcallback cb = NULL;
	card_block *card = &cardmap[chn];
	cb = card->card_api_cb;
	card->card_api_cb = NULL;

	ret = result;
	if(ret>=0 && (ret=__card_freeblock(chn,card->curr_fileblock,cb))>=0) return;

	__card_putcntrlblock(card,ret);
	if(cb) cb(chn,ret);
}
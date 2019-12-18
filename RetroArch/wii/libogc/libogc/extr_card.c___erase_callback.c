#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  (* cardcallback ) (size_t,size_t) ;
struct TYPE_5__ {int iblock; } ;
typedef  TYPE_1__ card_file ;
struct TYPE_6__ {int sector_size; int /*<<< orphan*/  (* card_api_cb ) (size_t,size_t) ;int /*<<< orphan*/  cmd_usr_buf; TYPE_1__* curr_file; } ;
typedef  TYPE_2__ card_block ;

/* Variables and functions */
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_2__*,size_t) ; 
 size_t __card_write (size_t,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __write_callback ; 
 TYPE_2__* cardmap ; 

__attribute__((used)) static void __erase_callback(s32 chn,s32 result)
{
	s32 ret;
	cardcallback cb = NULL;
	card_file *file = NULL;
	card_block *card = &cardmap[chn];
	ret = result;
	if(ret>=0) {
		file = card->curr_file;
		if((ret=__card_write(chn,(file->iblock*card->sector_size),card->sector_size,card->cmd_usr_buf,__write_callback))>=0) return;
	}

	cb = card->card_api_cb;
	card->card_api_cb = NULL;
	__card_putcntrlblock(card,ret);
	if(cb) cb(chn,ret);
}
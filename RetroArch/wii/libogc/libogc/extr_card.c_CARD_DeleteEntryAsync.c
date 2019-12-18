#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct card_direntry {int /*<<< orphan*/  block; } ;
struct card_dat {struct card_direntry* entries; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/ * cardcallback ;
struct TYPE_7__ {size_t fileno; } ;
typedef  TYPE_1__ card_dir ;
struct TYPE_8__ {int /*<<< orphan*/ * card_api_cb; int /*<<< orphan*/  curr_fileblock; } ;
typedef  TYPE_2__ card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_NOCARD ; 
 scalar_t__ EXI_CHANNEL_0 ; 
 scalar_t__ EXI_CHANNEL_2 ; 
 int /*<<< orphan*/ * __card_defaultapicallback ; 
 scalar_t__ __card_getcntrlblock (scalar_t__,TYPE_2__**) ; 
 struct card_dat* __card_getdirblock (TYPE_2__*) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_2__*,scalar_t__) ; 
 scalar_t__ __card_updatedir (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __delete_callback ; 
 int /*<<< orphan*/  memset (struct card_direntry*,int,int) ; 

s32 CARD_DeleteEntryAsync(s32 chn,card_dir *dir_entry,cardcallback callback)
{
	s32 ret;
	cardcallback cb = NULL;
	card_block *card = NULL;
	struct card_dat *dirblock = NULL;
	struct card_direntry *entry = NULL;
	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;
	if((ret=__card_getcntrlblock(chn,&card))<0) return ret;

	dirblock = __card_getdirblock(card);
	entry = &dirblock->entries[dir_entry->fileno];

	card->curr_fileblock = entry->block;
	memset(entry,-1,sizeof(struct card_direntry));

	cb = callback;
	if(!cb) cb = __card_defaultapicallback;
	card->card_api_cb = cb;

	if((ret=__card_updatedir(chn,__delete_callback))>=0) return ret;

	__card_putcntrlblock(card,ret);
	return ret;
}
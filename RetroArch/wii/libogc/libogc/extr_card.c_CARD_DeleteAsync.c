#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct card_direntry {int /*<<< orphan*/  block; } ;
struct card_dat {struct card_direntry* entries; } ;
typedef  size_t s32 ;
typedef  int /*<<< orphan*/ * cardcallback ;
struct TYPE_6__ {int /*<<< orphan*/ * card_api_cb; int /*<<< orphan*/  curr_fileblock; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 int /*<<< orphan*/ * __card_defaultapicallback ; 
 size_t __card_getcntrlblock (size_t,TYPE_1__**) ; 
 struct card_dat* __card_getdirblock (TYPE_1__*) ; 
 size_t __card_getfilenum (TYPE_1__*,char const*,char const*,char const*,size_t*) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_1__*,size_t) ; 
 size_t __card_updatedir (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __delete_callback ; 
 scalar_t__ card_company ; 
 scalar_t__ card_gamecode ; 
 int /*<<< orphan*/  memset (struct card_direntry*,int,int) ; 

s32 CARD_DeleteAsync(s32 chn,const char *filename,cardcallback callback)
{
	s32 ret,fileno;
	cardcallback cb = NULL;
	card_block *card = NULL;
	struct card_dat *dirblock = NULL;
	struct card_direntry *entry = NULL;
	if((ret=__card_getcntrlblock(chn,&card))<0) return ret;
	if((ret=__card_getfilenum(card,filename,(const char*)card_gamecode,(const char*)card_company,&fileno))<0) {
		__card_putcntrlblock(card,ret);
		return ret;
	}

	dirblock = __card_getdirblock(card);
	entry = &dirblock->entries[fileno];

	card->curr_fileblock = entry->block;
	memset(entry,-1,sizeof(struct card_direntry));

	cb = callback;
	if(!cb) cb = __card_defaultapicallback;
	card->card_api_cb = cb;

	if((ret=__card_updatedir(chn,__delete_callback))>=0) return ret;

	__card_putcntrlblock(card,ret);
	return ret;
}
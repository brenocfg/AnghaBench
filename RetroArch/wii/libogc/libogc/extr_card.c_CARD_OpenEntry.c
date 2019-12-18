#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct card_dat {TYPE_1__* entries; } ;
typedef  scalar_t__ s32 ;
struct TYPE_12__ {int filenum; int len; int iblock; scalar_t__ offset; scalar_t__ chn; } ;
typedef  TYPE_2__ card_file ;
struct TYPE_13__ {int fileno; scalar_t__ company; scalar_t__ gamecode; scalar_t__ filename; } ;
typedef  TYPE_3__ card_dir ;
struct TYPE_14__ {int blocks; int sector_size; } ;
typedef  TYPE_4__ card_block ;
struct TYPE_11__ {int block; int length; } ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_BROKEN ; 
 scalar_t__ CARD_ERROR_NOCARD ; 
 scalar_t__ CARD_ERROR_READY ; 
 scalar_t__ EXI_CHANNEL_0 ; 
 scalar_t__ EXI_CHANNEL_2 ; 
 scalar_t__ __card_getcntrlblock (scalar_t__,TYPE_4__**) ; 
 struct card_dat* __card_getdirblock (TYPE_4__*) ; 
 scalar_t__ __card_getfilenum (TYPE_4__*,char const*,char const*,char const*,scalar_t__*) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_4__*,scalar_t__) ; 

s32 CARD_OpenEntry(s32 chn,card_dir *entry,card_file *file)
{
	s32 ret,fileno;
	struct card_dat *dirblock = NULL;
	card_block *card = NULL;

	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;

	file->filenum = -1;
	if((ret=__card_getcntrlblock(chn,&card))<0) return ret;
	if((ret=__card_getfilenum(card,(const char*)entry->filename,(const char*)entry->gamecode,(const char*)entry->company,&fileno))<0) {
		__card_putcntrlblock(card,ret);
		return ret;
	}

	dirblock = __card_getdirblock(card);
	if(dirblock->entries[fileno].block<5 || dirblock->entries[fileno].block>=card->blocks) {
		__card_putcntrlblock(card,CARD_ERROR_BROKEN);
		return CARD_ERROR_BROKEN;
	}

	file->chn = chn;
	file->filenum = entry->fileno;
	file->offset = 0;
	file->len = dirblock->entries[fileno].length*card->sector_size;
	file->iblock = dirblock->entries[fileno].block;

	__card_putcntrlblock(card,CARD_ERROR_READY);
	return CARD_ERROR_READY;
}
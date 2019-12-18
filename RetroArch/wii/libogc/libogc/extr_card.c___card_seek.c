#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct card_direntry {int* gamecode; scalar_t__ length; scalar_t__ block; } ;
struct card_dat {struct card_direntry* entries; } ;
struct card_bat {scalar_t__* fat; } ;
typedef  scalar_t__ s32 ;
struct TYPE_9__ {size_t filenum; scalar_t__ iblock; scalar_t__ offset; scalar_t__ len; int /*<<< orphan*/  chn; } ;
typedef  TYPE_1__ card_file ;
struct TYPE_10__ {scalar_t__ blocks; scalar_t__ sector_size; TYPE_1__* curr_file; } ;
typedef  TYPE_2__ card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_BROKEN ; 
 scalar_t__ CARD_ERROR_FATAL_ERROR ; 
 scalar_t__ CARD_ERROR_LIMIT ; 
 scalar_t__ CARD_ERROR_READY ; 
 size_t CARD_MAXFILES ; 
 scalar_t__ CARD_SYSAREA ; 
 struct card_bat* __card_getbatblock (TYPE_2__*) ; 
 scalar_t__ __card_getcntrlblock (int /*<<< orphan*/ ,TYPE_2__**) ; 
 struct card_dat* __card_getdirblock (TYPE_2__*) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static s32 __card_seek(card_file *file,s32 len,s32 offset,card_block **rcard)
{
	s32 ret;
	s32 i,entry_len;
	card_block *card = NULL;
	struct card_direntry *entry = NULL;
	struct card_dat *dirblock = NULL;
	struct card_bat *fatblock = NULL;
	if(file->filenum<0 || file->filenum>=CARD_MAXFILES) return CARD_ERROR_FATAL_ERROR;
	if((ret=__card_getcntrlblock(file->chn,&card))<0) return ret;
	if(file->iblock<CARD_SYSAREA || file->iblock>=card->blocks) {
		__card_putcntrlblock(card,CARD_ERROR_FATAL_ERROR);
		return CARD_ERROR_FATAL_ERROR;
	}

	dirblock = __card_getdirblock(card);
	entry = &dirblock->entries[file->filenum];
	if(entry->gamecode[0]!=0xff) {
		entry_len = entry->length*card->sector_size;
		if(entry_len<offset || entry_len<(offset+len)) {
			__card_putcntrlblock(card,CARD_ERROR_LIMIT);
			return CARD_ERROR_LIMIT;
		}
		card->curr_file = file;
		file->len = len;

		if(offset<file->offset) {
			file->offset = 0;
			file->iblock = entry->block;
			if(file->iblock<CARD_SYSAREA || file->iblock>=card->blocks) {
				__card_putcntrlblock(card,CARD_ERROR_BROKEN);
				return CARD_ERROR_BROKEN;
			}
		}

		fatblock = __card_getbatblock(card);
		for(i=file->iblock;i<card->blocks && file->offset<(offset&~(card->sector_size-1));i=file->iblock) {
			file->offset += card->sector_size;
			file->iblock = fatblock->fat[i-CARD_SYSAREA];
			if(file->iblock<CARD_SYSAREA || file->iblock>=card->blocks) {
				__card_putcntrlblock(card,CARD_ERROR_BROKEN);
				return CARD_ERROR_BROKEN;
			}
		}
		file->offset = offset;
		*rcard = card;
	}
	return CARD_ERROR_READY;
}
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
struct card_direntry {int /*<<< orphan*/  lastmodified; } ;
struct card_dat {struct card_direntry* entries; } ;
struct card_bat {size_t* fat; } ;
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  (* cardcallback ) (size_t,size_t) ;
struct TYPE_7__ {scalar_t__ len; size_t filenum; int offset; size_t iblock; } ;
typedef  TYPE_1__ card_file ;
struct TYPE_8__ {int sector_size; size_t blocks; int /*<<< orphan*/  (* card_api_cb ) (size_t,size_t) ;TYPE_1__* curr_file; } ;
typedef  TYPE_2__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_BROKEN ; 
 size_t CARD_ERROR_CANCELED ; 
 size_t CARD_SYSAREA ; 
 struct card_bat* __card_getbatblock (TYPE_2__*) ; 
 struct card_dat* __card_getdirblock (TYPE_2__*) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_2__*,size_t) ; 
 size_t __card_sectorerase (size_t,int,int /*<<< orphan*/ ) ; 
 size_t __card_updatedir (size_t,int /*<<< orphan*/  (*) (size_t,size_t)) ; 
 int /*<<< orphan*/  __erase_callback ; 
 TYPE_2__* cardmap ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __write_callback(s32 chn,s32 result)
{
	s32 ret;
	cardcallback cb = NULL;
	card_file *file = NULL;
	struct card_bat *fatblock = NULL;
	struct card_dat *dirblock = NULL;
	struct card_direntry *entry = NULL;
	card_block *card = &cardmap[chn];
	ret = result;
	if(ret>=0) {
		file = card->curr_file;
		if(file->len>=0) {
			file->len = (card->sector_size-file->len);
			if(file->len<=0) {
				dirblock = __card_getdirblock(card);
				entry = &dirblock->entries[file->filenum];
				entry->lastmodified = time(NULL);
				cb = card->card_api_cb;
				card->card_api_cb = NULL;
				if((ret=__card_updatedir(chn,cb))>=0) return;
			} else {
				fatblock = __card_getbatblock(card);
				file->offset += card->sector_size;
				file->iblock = fatblock->fat[file->iblock-CARD_SYSAREA];
				if(file->iblock<CARD_SYSAREA || file->iblock>=card->blocks) {
					ret = CARD_ERROR_BROKEN;
					goto exit;
				}
				if((ret=__card_sectorerase(chn,(file->iblock*card->sector_size),__erase_callback))>=0) return;
			}
		} else
			ret = CARD_ERROR_CANCELED;
	}

exit:
	cb = card->card_api_cb;
	card->card_api_cb = NULL;
	__card_putcntrlblock(card,ret);
	if(cb) cb(chn,ret);
}
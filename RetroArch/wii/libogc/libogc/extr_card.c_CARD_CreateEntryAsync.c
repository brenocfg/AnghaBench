#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct card_direntry {int* gamecode; int* filename; int* company; int length; } ;
struct card_dat {struct card_direntry* entries; } ;
struct card_bat {int freeblocks; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/ * cardcallback ;
struct TYPE_10__ {int chn; int filenum; } ;
typedef  TYPE_1__ card_file ;
struct TYPE_11__ {int* filename; int filelen; } ;
typedef  TYPE_2__ card_dir ;
struct TYPE_12__ {int sector_size; TYPE_1__* curr_file; int /*<<< orphan*/ * card_api_cb; } ;
typedef  TYPE_3__ card_block ;

/* Variables and functions */
 int CARD_ERROR_EXIST ; 
 int CARD_ERROR_FATAL_ERROR ; 
 int CARD_ERROR_INSSPACE ; 
 int CARD_ERROR_NAMETOOLONG ; 
 int CARD_ERROR_NOENT ; 
 scalar_t__ CARD_FILENAMELEN ; 
 scalar_t__ CARD_MAXFILES ; 
 int __card_allocblock (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_createfatcallback ; 
 int /*<<< orphan*/ * __card_defaultapicallback ; 
 struct card_bat* __card_getbatblock (TYPE_3__*) ; 
 int __card_getcntrlblock (int,TYPE_3__**) ; 
 struct card_dat* __card_getdirblock (TYPE_3__*) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_3__*,int) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

s32 CARD_CreateEntryAsync(s32 chn,card_dir *direntry,card_file *file,cardcallback callback)
{
	u32 i,len;
	s32 ret,filenum;
	cardcallback cb = NULL;
	card_block *card = NULL;
	struct card_bat *fatblock = NULL;
	struct card_dat *dirblock = NULL;
	struct card_direntry *entry = NULL;
	len = strlen((const char*)direntry->filename);
	if(len>CARD_FILENAMELEN) return CARD_ERROR_NAMETOOLONG;

	if((ret=__card_getcntrlblock(chn,&card))<0) return ret;
	if(direntry->filelen<=0 || direntry->filelen%card->sector_size) return CARD_ERROR_FATAL_ERROR;

	dirblock = __card_getdirblock(card);

	filenum = -1;
	entry = dirblock->entries;
	for(i=0;i<CARD_MAXFILES;i++) {
		if(entry[i].gamecode[0]==0xff) {
			if(filenum==-1) filenum = i;
		} else if(memcmp(entry[i].filename,direntry->filename,len)==0) {
			if((entry->gamecode[0]==0xff || entry->company[0]==0xff)
				|| ((entry->gamecode[0]!=0xff && memcmp(entry[i].gamecode,entry->gamecode,4)==0)
				&& (entry->company[0]!=0xff && memcmp(entry[i].company,entry->company,2)==0))) {
				__card_putcntrlblock(card,CARD_ERROR_EXIST);
				return CARD_ERROR_EXIST;
			}
		}
	}
	if(filenum==-1) {
		__card_putcntrlblock(card,CARD_ERROR_NOENT);
		return CARD_ERROR_NOENT;
	}

	fatblock = __card_getbatblock(card);
	if((fatblock->freeblocks*card->sector_size)<direntry->filelen) {
		__card_putcntrlblock(card,CARD_ERROR_INSSPACE);
		return CARD_ERROR_INSSPACE;
	}

	cb = callback;
	if(!cb) cb = __card_defaultapicallback;
	card->card_api_cb = cb;

	entry[filenum].length = direntry->filelen/card->sector_size;
	memset(entry[filenum].filename,0,CARD_FILENAMELEN);
	memcpy(entry[filenum].filename,direntry->filename,len+1);

	card->curr_file = file;
	file->chn = chn;
	file->filenum = filenum;
	if((ret=__card_allocblock(chn,(direntry->filelen/card->sector_size),__card_createfatcallback))<0) {
		__card_putcntrlblock(card,ret);
		return ret;
	}

	return 0;
}
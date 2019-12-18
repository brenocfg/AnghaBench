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
struct card_direntry {int* gamecode; int* company; int length; int* filename; } ;
struct card_dat {struct card_direntry* entries; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_7__ {scalar_t__ chn; size_t fileno; int filelen; int /*<<< orphan*/  company; int /*<<< orphan*/  gamecode; int /*<<< orphan*/  filename; scalar_t__ showall; } ;
typedef  TYPE_1__ card_dir ;
struct TYPE_8__ {int sector_size; int /*<<< orphan*/  attached; } ;
typedef  TYPE_2__ card_block ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_ERROR_NOCARD ; 
 int /*<<< orphan*/  CARD_ERROR_NOFILE ; 
 int /*<<< orphan*/  CARD_ERROR_READY ; 
 int CARD_FILENAMELEN ; 
 size_t CARD_MAXFILES ; 
 scalar_t__ EXI_CHANNEL_0 ; 
 scalar_t__ EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  __card_getcntrlblock (scalar_t__,TYPE_2__**) ; 
 struct card_dat* __card_getdirblock (TYPE_2__*) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  card_company ; 
 int /*<<< orphan*/  card_gamecode ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

s32 __card_findnext(card_dir *dir)
{
	s32 ret;
	struct card_dat *dirblock = NULL;
	struct card_direntry *entries = NULL;
	card_block *card = NULL;

	if(dir->chn<EXI_CHANNEL_0 || dir->chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;
	if(dir->fileno>=CARD_MAXFILES) return CARD_ERROR_NOFILE;
	if((ret=__card_getcntrlblock(dir->chn,&card))<0) return ret;

	if(!card->attached) return CARD_ERROR_NOCARD;
	dirblock = __card_getdirblock(card);

	entries = dirblock->entries;
	do {
		//printf("%s\n", entries[dir->fileno].filename);
		if(entries[dir->fileno].gamecode[0]!=0xff) {
			if ((dir->showall || memcmp(entries[dir->fileno].gamecode,card_gamecode,4)==0)
				&& (dir->showall || memcmp(entries[dir->fileno].company,card_company,2)==0)) {
				dir->filelen = entries[dir->fileno].length*card->sector_size;
				memcpy(dir->filename, entries[dir->fileno].filename, CARD_FILENAMELEN);
				memcpy(dir->gamecode, entries[dir->fileno].gamecode, 4);
				memcpy(dir->company, entries[dir->fileno].company, 2);

				__card_putcntrlblock(card,CARD_ERROR_READY);
				return CARD_ERROR_READY;
			}
		}
		dir->fileno++;
	} while (dir->fileno < CARD_MAXFILES);
	__card_putcntrlblock(card,CARD_ERROR_NOFILE);
	return CARD_ERROR_NOFILE;
}
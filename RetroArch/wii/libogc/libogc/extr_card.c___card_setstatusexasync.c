#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct card_direntry {int* filename; scalar_t__* gamecode; scalar_t__* company; int /*<<< orphan*/  copytimes; int /*<<< orphan*/  permission; int /*<<< orphan*/  commentaddr; int /*<<< orphan*/  iconspeed; int /*<<< orphan*/  iconfmt; int /*<<< orphan*/  iconaddr; int /*<<< orphan*/  bannerfmt; int /*<<< orphan*/  lastmodified; } ;
struct card_dat {struct card_direntry* entries; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  cardcallback ;
typedef  int /*<<< orphan*/  card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_BROKEN ; 
 scalar_t__ CARD_ERROR_EXIST ; 
 scalar_t__ CARD_ERROR_FATAL_ERROR ; 
 scalar_t__ CARD_ERROR_NOCARD ; 
 scalar_t__ CARD_ERROR_READY ; 
 scalar_t__ CARD_FILENAMELEN ; 
 scalar_t__ CARD_MAXFILES ; 
 scalar_t__ EXI_CHANNEL_0 ; 
 scalar_t__ EXI_CHANNEL_2 ; 
 scalar_t__ __card_getcntrlblock (scalar_t__,int /*<<< orphan*/ **) ; 
 struct card_dat* __card_getdirblock (int /*<<< orphan*/ *) ; 
 scalar_t__ __card_putcntrlblock (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ __card_updatedir (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static s32 __card_setstatusexasync(s32 chn,s32 fileno,struct card_direntry *entry,cardcallback callback)
{
	s32 ret,i,bend;
	card_block *card = NULL;
	struct card_dat *dirblock = NULL;
	struct card_direntry *entries = NULL;

	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;
	if(fileno<0 || fileno>=CARD_MAXFILES) return CARD_ERROR_FATAL_ERROR;
	if(entry->filename[0]==0xff || entry->filename[0]==0) return CARD_ERROR_FATAL_ERROR;
	if((ret=__card_getcntrlblock(chn,&card))<0) return ret;

	ret = CARD_ERROR_BROKEN;
	dirblock = __card_getdirblock(card);
	if(dirblock) {
		i = 0; bend = 0;
		ret = CARD_ERROR_READY;
		entries = dirblock->entries;
		while(i<CARD_FILENAMELEN) {
			if(bend || entry->filename[i]==0) {
				entry->filename[i] = 0;
				bend = 1;
			}
			i++;
		}

		if(memcmp(entries[fileno].filename,entry->filename,CARD_FILENAMELEN)
			|| memcmp(entries[fileno].gamecode,entry->gamecode,4)
			|| memcmp(entries[fileno].company,entry->company,2)) {
			i = 0;
			while(i<CARD_MAXFILES) {
				if(i!=fileno && entries[i].gamecode[0]!=0xff
					&& memcmp(entries[i].gamecode,entry->gamecode,4)==0
					&& memcmp(entries[i].company,entry->company,2)==0
					&& memcmp(entries[i].filename,entry->filename,CARD_FILENAMELEN)==0) {
					return __card_putcntrlblock(card,CARD_ERROR_EXIST);
				}
				i++;
			}
			memcpy(entries[fileno].filename,entry->filename,CARD_FILENAMELEN);
			memcpy(entries[fileno].gamecode,entry->gamecode,4);
			memcpy(entries[fileno].company,entry->company,2);
		}

		entries[fileno].lastmodified = entry->lastmodified;
		entries[fileno].bannerfmt = entry->bannerfmt;
		entries[fileno].iconaddr = entry->iconaddr;
		entries[fileno].iconfmt = entry->iconfmt;
		entries[fileno].iconspeed = entry->iconspeed;
		entries[fileno].commentaddr = entry->commentaddr;
		entries[fileno].permission = entry->permission;
		entries[fileno].copytimes = entry->copytimes;

		if((ret=__card_updatedir(chn,callback))>=0) return ret;
	}
	return __card_putcntrlblock(card,ret);
}
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
struct card_direntry {int* gamecode; int* company; int length; int* filename; int /*<<< orphan*/  permission; } ;
struct card_dat {struct card_direntry* entries; } ;
typedef  scalar_t__ s32 ;
struct TYPE_7__ {int filelen; int /*<<< orphan*/  filename; int /*<<< orphan*/  company; int /*<<< orphan*/  gamecode; int /*<<< orphan*/  permissions; scalar_t__ fileno; } ;
typedef  TYPE_1__ card_dir ;
struct TYPE_8__ {int sector_size; int /*<<< orphan*/  attached; } ;
typedef  TYPE_2__ card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_NOCARD ; 
 scalar_t__ CARD_ERROR_NOFILE ; 
 scalar_t__ CARD_ERROR_READY ; 
 int CARD_FILENAMELEN ; 
 scalar_t__ CARD_MAXFILES ; 
 scalar_t__ EXI_CHANNEL_0 ; 
 scalar_t__ EXI_CHANNEL_2 ; 
 scalar_t__ __card_getcntrlblock (scalar_t__,TYPE_2__**) ; 
 struct card_dat* __card_getdirblock (TYPE_2__*) ; 
 int /*<<< orphan*/  __card_putcntrlblock (TYPE_2__*,scalar_t__) ; 
 int* card_company ; 
 int* card_gamecode ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

s32 CARD_GetDirectory(s32 chn,card_dir *dir_entries,s32 *count,bool showall)
{
	s32 i,cnt;
	s32 ret = CARD_ERROR_READY;
	struct card_dat *dirblock = NULL;
	struct card_direntry *entries = NULL;
	card_block *card = NULL;

	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;
	if((ret=__card_getcntrlblock(chn,&card))<0) return ret;

	if(!card->attached) return CARD_ERROR_NOCARD;
	dirblock = __card_getdirblock(card);

	entries = dirblock->entries;
	for(i=0,cnt=0;i<CARD_MAXFILES;i++) {
		if(entries[i].gamecode[0]!=0xff) {
			if(showall || ((card_gamecode[0]!=0xff && memcmp(entries[i].gamecode,card_gamecode,4)==0)
				&& (card_company[0]!=0xff && memcmp(entries[i].company,card_company,2)==0))) {
				dir_entries[cnt].fileno = i;
				dir_entries[cnt].permissions = entries[i].permission;
				dir_entries[cnt].filelen = entries[i].length*card->sector_size;
				memcpy(dir_entries[cnt].gamecode,entries[i].gamecode,4);
				memcpy(dir_entries[cnt].company,entries[i].company,2);
				memcpy(dir_entries[cnt].filename,entries[i].filename,CARD_FILENAMELEN);
				cnt++;
			}
		}
	}
	if(count) *count = cnt;
	if(cnt==0) ret = CARD_ERROR_NOFILE;
	__card_putcntrlblock(card,ret);
	return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct card_bat {scalar_t__ chksum1; scalar_t__ chksum2; scalar_t__ freeblocks; scalar_t__ updated; int /*<<< orphan*/ * fat; } ;
struct TYPE_3__ {scalar_t__ blocks; struct card_bat* curr_fat; struct card_bat* workarea; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 scalar_t__ CARD_SYSAREA ; 
 int /*<<< orphan*/  __card_checksum (scalar_t__*,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (struct card_bat*,struct card_bat*,int) ; 

__attribute__((used)) static u32 __card_checkfat(card_block *card,u32 *currfat)
{
	u32 fat,bad,bad_fat;
	u16 chksum0,chksum1;
	struct card_bat *fatblock[2];
	fat = 0;
	bad = 0;
	bad_fat = 0;
	while(fat<2) {
		fatblock[fat] = card->workarea+((fat+3)<<13);
		__card_checksum((u16*)(((u32)fatblock[fat])+4),0x1ffc,&chksum0,&chksum1);
		if(chksum0!=fatblock[fat]->chksum1 || chksum1!=fatblock[fat]->chksum2) {
			card->curr_fat = NULL;
			bad_fat = fat;
			bad++;
		} else {
			u16 curblock = CARD_SYSAREA;
			u16 freeblocks = 0;
			while(curblock<card->blocks) {
				if(!fatblock[fat]->fat[curblock-CARD_SYSAREA]) freeblocks++;
				curblock++;
			}
			if(freeblocks!=fatblock[fat]->freeblocks) {
				card->curr_fat = NULL;
				bad_fat = fat;
				bad++;
			}
		}
		fat++;
	}

	fat = bad_fat;
	if(!bad) {
		if(fatblock[0]->updated<fatblock[1]->updated) fat = 0;
		else fat = 1;
	}
	if(card->curr_fat==NULL) {
		card->curr_fat = fatblock[fat];
		memcpy(fatblock[fat],fatblock[fat^1],8192);
	}
	else if(card->curr_fat==fatblock[0]) fat = 0;
	else fat = 1;

	if(currfat) *currfat = fat;
	return bad;
}
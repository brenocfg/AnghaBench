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
struct card_direntry {int dummy; } ;
struct card_dat {int /*<<< orphan*/ * entries; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_BROKEN ; 
 scalar_t__ CARD_ERROR_FATAL_ERROR ; 
 scalar_t__ CARD_ERROR_NOCARD ; 
 scalar_t__ CARD_ERROR_READY ; 
 scalar_t__ CARD_MAXFILES ; 
 scalar_t__ EXI_CHANNEL_0 ; 
 scalar_t__ EXI_CHANNEL_2 ; 
 scalar_t__ __card_getcntrlblock (scalar_t__,int /*<<< orphan*/ **) ; 
 struct card_dat* __card_getdirblock (int /*<<< orphan*/ *) ; 
 scalar_t__ __card_putcntrlblock (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct card_direntry*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static s32 __card_getstatusex(s32 chn,s32 fileno,struct card_direntry *entry)
{
	s32 ret;
	card_block *card = NULL;
	struct card_dat *dirblock = NULL;

	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;
	if(fileno<0 || fileno>=CARD_MAXFILES) return CARD_ERROR_FATAL_ERROR;
	if((ret=__card_getcntrlblock(chn,&card))<0) return ret;

	ret = CARD_ERROR_BROKEN;
	dirblock = __card_getdirblock(card);
	if(dirblock) {
		ret = CARD_ERROR_READY;
		memcpy(entry,&dirblock->entries[fileno],sizeof(struct card_direntry));
	}
	return __card_putcntrlblock(card,ret);
}
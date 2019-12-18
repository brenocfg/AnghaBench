#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct card_direntry {int iconaddr; int iconfmt; int commentaddr; int /*<<< orphan*/  lastmodified; int /*<<< orphan*/  iconspeed; int /*<<< orphan*/  bannerfmt; } ;
struct card_dat {struct card_direntry* entries; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  cardcallback ;
struct TYPE_4__ {int icon_addr; int comment_addr; int icon_fmt; int /*<<< orphan*/  icon_speed; int /*<<< orphan*/  banner_fmt; } ;
typedef  TYPE_1__ card_stat ;
typedef  int /*<<< orphan*/  card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_BROKEN ; 
 scalar_t__ CARD_ERROR_FATAL_ERROR ; 
 scalar_t__ CARD_ERROR_NOCARD ; 
 int CARD_ICON_CI ; 
 int CARD_ICON_MASK ; 
 scalar_t__ CARD_MAXFILES ; 
 int CARD_READSIZE ; 
 scalar_t__ EXI_CHANNEL_0 ; 
 scalar_t__ EXI_CHANNEL_2 ; 
 scalar_t__ __card_getcntrlblock (scalar_t__,int /*<<< orphan*/ **) ; 
 struct card_dat* __card_getdirblock (int /*<<< orphan*/ *) ; 
 scalar_t__ __card_putcntrlblock (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ __card_updatedir (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_updateiconoffsets (struct card_direntry*,TYPE_1__*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

s32 CARD_SetStatusAsync(s32 chn,s32 fileno,card_stat *stats,cardcallback callback)
{
	s32 ret;
	card_block *card = NULL;
	struct card_dat *dirblock = NULL;
	struct card_direntry *entry = NULL;

	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;
	if(fileno<0 || fileno>=CARD_MAXFILES) return CARD_ERROR_FATAL_ERROR;
	if(stats->icon_addr!=-1 && stats->icon_addr>CARD_READSIZE) return CARD_ERROR_FATAL_ERROR;
	if(stats->comment_addr!=-1 && stats->comment_addr>8128) return CARD_ERROR_FATAL_ERROR;
	if((ret=__card_getcntrlblock(chn,&card))<0) return ret;

	ret = CARD_ERROR_BROKEN;
	dirblock = __card_getdirblock(card);
	if(dirblock) {
		entry = &dirblock->entries[fileno];
		entry->bannerfmt = stats->banner_fmt;
		entry->iconaddr = stats->icon_addr;
		entry->iconfmt = stats->icon_fmt;
		entry->iconspeed = stats->icon_speed;
		entry->commentaddr = stats->comment_addr;
		__card_updateiconoffsets(entry,stats);

		if(entry->iconaddr==-1) entry->iconfmt = ((entry->iconfmt&~CARD_ICON_MASK)|CARD_ICON_CI);

		entry->lastmodified = time(NULL);
		if((ret=__card_updatedir(chn,callback))>=0) return ret;
	}

	return __card_putcntrlblock(card,ret);
}
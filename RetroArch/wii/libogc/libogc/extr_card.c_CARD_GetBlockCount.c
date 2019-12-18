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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {int /*<<< orphan*/  blocks; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_NOCARD ; 
 int /*<<< orphan*/  CARD_ERROR_READY ; 
 scalar_t__ EXI_CHANNEL_0 ; 
 scalar_t__ EXI_CHANNEL_2 ; 
 scalar_t__ __card_getcntrlblock (scalar_t__,TYPE_1__**) ; 
 scalar_t__ __card_putcntrlblock (TYPE_1__*,int /*<<< orphan*/ ) ; 

s32 CARD_GetBlockCount(s32 chn,u32 *block_count)
{
	s32 ret;
	card_block *card = NULL;

	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;
	if((ret=__card_getcntrlblock(chn,&card))<0) return ret;

	*block_count = card->blocks;
	ret = __card_putcntrlblock(card,CARD_ERROR_READY);

	return ret;
}
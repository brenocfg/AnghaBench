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
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_NOCARD ; 
 scalar_t__ CARD_ERROR_READY ; 
 scalar_t__ EXI_CHANNEL_0 ; 
 scalar_t__ EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  __card_dounmount (scalar_t__,scalar_t__) ; 
 scalar_t__ __card_getcntrlblock (scalar_t__,int /*<<< orphan*/ **) ; 

s32 CARD_Unmount(s32 chn)
{
	s32 ret;
	card_block *card = NULL;

	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;

	if((ret=__card_getcntrlblock(chn,&card))<0) ret = CARD_ERROR_NOCARD;

	__card_dounmount(chn,ret);
	return CARD_ERROR_READY;
}
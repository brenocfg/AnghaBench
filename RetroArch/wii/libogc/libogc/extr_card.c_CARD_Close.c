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
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_3__ {int chn; scalar_t__ filenum; } ;
typedef  TYPE_1__ card_file ;
typedef  int /*<<< orphan*/  card_block ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_ERROR_NOCARD ; 
 int /*<<< orphan*/  CARD_ERROR_NOFILE ; 
 int /*<<< orphan*/  CARD_ERROR_READY ; 
 scalar_t__ CARD_MAXFILES ; 
 int EXI_CHANNEL_0 ; 
 int EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  __card_getcntrlblock (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  __card_putcntrlblock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

s32 CARD_Close(card_file *file)
{
	s32 ret;
	card_block *card = NULL;

	if(file->chn<EXI_CHANNEL_0 || file->chn>=EXI_CHANNEL_2)	return CARD_ERROR_NOCARD;
	if(file->filenum<0 || file->filenum>=CARD_MAXFILES) return CARD_ERROR_NOFILE;
	if((ret=__card_getcntrlblock(file->chn,&card))<0) return ret;

	file->chn = -1;
	__card_putcntrlblock(card,CARD_ERROR_READY);
	return CARD_ERROR_READY;
}
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
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  cardcallback ;
struct TYPE_3__ {int* cmd; int cmd_sector_addr; int cmd_len; int cmd_retries; int /*<<< orphan*/ * card_exi_cb; int /*<<< orphan*/  cmd_mode; int /*<<< orphan*/  cmd_usr_buf; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_NOCARD ; 
 size_t CARD_ERROR_READY ; 
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  EXI_Deselect (size_t) ; 
 int EXI_Dma (size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EXI_ImmEx (size_t,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXI_Unlock (size_t) ; 
 int /*<<< orphan*/  EXI_WRITE ; 
 size_t __card_start (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __card_txhandler ; 
 TYPE_1__* cardmap ; 

__attribute__((used)) static s32 __card_writepage(s32 chn,cardcallback callback)
{
	s32 ret;
	card_block *card = NULL;
	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return CARD_ERROR_NOCARD;
	card = &cardmap[chn];

	card->cmd[0] = 0xf2;
	card->cmd[1] = (card->cmd_sector_addr>>17)&0x3f;
	card->cmd[2] = (card->cmd_sector_addr>>9)&0xff;
	card->cmd[3] = (card->cmd_sector_addr>>7)&3;
	card->cmd[4] = card->cmd_sector_addr&0x7f;
	card->cmd_len = 5;
	card->cmd_mode = EXI_WRITE;
	card->cmd_retries = 3;

	ret = __card_start(chn,NULL,callback);
	if(ret<0) return ret;

	if(EXI_ImmEx(chn,card->cmd,card->cmd_len,EXI_WRITE)==1
		&& EXI_Dma(chn,card->cmd_usr_buf,128,card->cmd_mode,__card_txhandler)==1) return CARD_ERROR_READY;

	card->card_exi_cb = NULL;
	EXI_Deselect(chn);
	EXI_Unlock(chn);
	return CARD_ERROR_NOCARD;
}
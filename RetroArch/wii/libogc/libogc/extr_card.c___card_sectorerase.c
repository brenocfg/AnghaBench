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
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  cardcallback ;
struct TYPE_3__ {int sector_size; int* cmd; int cmd_len; int cmd_mode; int cmd_retries; int /*<<< orphan*/ * card_exi_cb; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_FATAL_ERROR ; 
 size_t CARD_ERROR_NOCARD ; 
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  EXI_Deselect (size_t) ; 
 scalar_t__ EXI_ImmEx (size_t,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXI_Unlock (size_t) ; 
 int /*<<< orphan*/  EXI_WRITE ; 
 size_t __card_start (size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* cardmap ; 

__attribute__((used)) static s32 __card_sectorerase(s32 chn,u32 sector,cardcallback callback)
{
	s32 ret;
	card_block *card = NULL;
	if(chn<EXI_CHANNEL_0 || chn>= EXI_CHANNEL_2) return CARD_ERROR_FATAL_ERROR;
	card = &cardmap[chn];

	if(sector%card->sector_size) return CARD_ERROR_FATAL_ERROR;

	card->cmd[0] = 0xf1;
	card->cmd[1] = (sector>>17)&0x7f;
	card->cmd[2] = (sector>>9)&0xff;
	card->cmd_len = 3;
	card->cmd_mode = -1;
	card->cmd_retries = 3;

	ret = __card_start(chn,NULL,callback);
	if(ret<0) return ret;

	if(EXI_ImmEx(chn,card->cmd,card->cmd_len,EXI_WRITE)==0) {
		card->card_exi_cb = NULL;
		return CARD_ERROR_NOCARD;
	}

	EXI_Deselect(chn);
	EXI_Unlock(chn);
	return ret;
}
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
typedef  int /*<<< orphan*/  (* cardcallback ) (size_t,int /*<<< orphan*/ ) ;
struct TYPE_3__ {int /*<<< orphan*/  (* card_ext_cb ) (size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* card_exi_cb ) (size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  timeout_svc; scalar_t__ attached; scalar_t__ card_tx_cb; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_ERROR_NOCARD ; 
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  EXI_RegisterEXICallback (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_CancelAlarm (int /*<<< orphan*/ ) ; 
 TYPE_1__* cardmap ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static s32 __card_exthandler(s32 chn,s32 dev)
{
	cardcallback cb;
	card_block *card = NULL;
	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return 0;
	card = &cardmap[chn];

	if(card->attached) {
		if(card->card_tx_cb) {
			printf("error: card->card_tx_cb!=NULL\n");
		}
		card->attached = 0;
		EXI_RegisterEXICallback(chn,NULL);
		SYS_CancelAlarm(card->timeout_svc);

		cb = card->card_exi_cb;
		if(cb) {
			card->card_exi_cb = NULL;
			cb(chn,CARD_ERROR_NOCARD);
		}

		cb = card->card_ext_cb;
		if(cb) {
			card->card_ext_cb = NULL;
			cb(chn,CARD_ERROR_NOCARD);
		}

	}
	return 1;
}
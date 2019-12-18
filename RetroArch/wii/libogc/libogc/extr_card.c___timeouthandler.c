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
typedef  size_t u32 ;
typedef  scalar_t__ syswd_t ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  (* cardcallback ) (size_t,int /*<<< orphan*/ ) ;
struct TYPE_3__ {scalar_t__ timeout_svc; int /*<<< orphan*/  (* card_exi_cb ) (size_t,int /*<<< orphan*/ ) ;scalar_t__ attached; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_ERROR_IOERROR ; 
 int /*<<< orphan*/  CARD_ERROR_READY ; 
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  EXI_RegisterEXICallback (size_t,int /*<<< orphan*/ *) ; 
 TYPE_1__* cardmap ; 

__attribute__((used)) static void __timeouthandler(syswd_t alarm,void *cbarg)
{
	u32 chn;
	s32 ret = CARD_ERROR_READY;
	cardcallback cb;
	card_block *card = NULL;
	chn = 0;
	while(chn<EXI_CHANNEL_2) {
		card = &cardmap[chn];
		if(card->timeout_svc==alarm) break;
		chn++;
	}
	if(chn<EXI_CHANNEL_0 || chn>=EXI_CHANNEL_2) return;

	if(card->attached) {
		EXI_RegisterEXICallback(chn,NULL);
		cb = card->card_exi_cb;
		if(cb) {
			card->card_exi_cb = NULL;
			ret = CARD_ERROR_IOERROR;
			cb(chn,ret);
		}
	}
}
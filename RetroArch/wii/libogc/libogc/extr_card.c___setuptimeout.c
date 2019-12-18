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
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_3__ {int* cmd; int sector_size; int /*<<< orphan*/  timeout_svc; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_CancelAlarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_SetAlarm (int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int TB_NSPERMS ; 
 int /*<<< orphan*/  __timeouthandler ; 

__attribute__((used)) static void __setuptimeout(card_block *card)
{
	struct timespec tb;
	SYS_CancelAlarm(card->timeout_svc);

	if(card->cmd[0]==0xf1 || card->cmd[0]==0xf4) {
		tb.tv_sec = 1*(card->sector_size/8192);
		tb.tv_nsec = 0;
		SYS_SetAlarm(card->timeout_svc,&tb,__timeouthandler,NULL);
	} else if(card->cmd[0]==0xf2) {
		tb.tv_sec = 0;
		tb.tv_nsec = 100*TB_NSPERMS;
		SYS_SetAlarm(card->timeout_svc,&tb,__timeouthandler,NULL);
	}
}
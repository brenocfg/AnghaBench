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
struct TYPE_4__ {int order_time; int /*<<< orphan*/  decisionmaker; int /*<<< orphan*/  client; int /*<<< orphan*/  ordered; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_NEGATIVE ; 
 int /*<<< orphan*/  BotVoiceChat (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FloatTime () ; 
 int /*<<< orphan*/  VOICECHAT_NO ; 
 int /*<<< orphan*/  trap_EA_Action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BotRefuseOrder(bot_state_t *bs) {
	if (!bs->ordered)
		return;
	// if the bot was ordered to do something
	if ( bs->order_time && bs->order_time > FloatTime() - 10 ) {
		trap_EA_Action(bs->client, ACTION_NEGATIVE);
		BotVoiceChat(bs, bs->decisionmaker, VOICECHAT_NO);
		bs->order_time = 0;
	}
}
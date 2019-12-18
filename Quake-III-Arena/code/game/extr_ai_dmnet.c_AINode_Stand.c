#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ lastframe_health; scalar_t__* inventory; scalar_t__ standfindenemy_time; scalar_t__ stand_time; int /*<<< orphan*/  chatto; int /*<<< orphan*/  cs; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIEnter_Battle_Fight (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Seek_LTG (TYPE_1__*,char*) ; 
 scalar_t__ BotChatTime (TYPE_1__*) ; 
 scalar_t__ BotChat_HitTalking (TYPE_1__*) ; 
 scalar_t__ BotFindEnemy (TYPE_1__*,int) ; 
 scalar_t__ FloatTime () ; 
 size_t INVENTORY_HEALTH ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_EA_Talk (int /*<<< orphan*/ ) ; 

int AINode_Stand(bot_state_t *bs) {

	//if the bot's health decreased
	if (bs->lastframe_health > bs->inventory[INVENTORY_HEALTH]) {
		if (BotChat_HitTalking(bs)) {
			bs->standfindenemy_time = FloatTime() + BotChatTime(bs) + 0.1;
			bs->stand_time = FloatTime() + BotChatTime(bs) + 0.1;
		}
	}
	if (bs->standfindenemy_time < FloatTime()) {
		if (BotFindEnemy(bs, -1)) {
			AIEnter_Battle_Fight(bs, "stand: found enemy");
			return qfalse;
		}
		bs->standfindenemy_time = FloatTime() + 1;
	}
	// put up chat icon
	trap_EA_Talk(bs->client);
	// when done standing
	if (bs->stand_time < FloatTime()) {
		trap_BotEnterChat(bs->cs, 0, bs->chatto);
		AIEnter_Seek_LTG(bs, "stand: time out");
		return qfalse;
	}
	//
	return qtrue;
}
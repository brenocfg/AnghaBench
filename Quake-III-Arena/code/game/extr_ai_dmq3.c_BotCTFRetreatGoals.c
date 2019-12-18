#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ltgtype; int /*<<< orphan*/  ordered; int /*<<< orphan*/  client; int /*<<< orphan*/  decisionmaker; scalar_t__ rushbaseaway_time; scalar_t__ teamgoal_time; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 scalar_t__ BotCTFCarryingFlag (TYPE_1__*) ; 
 int /*<<< orphan*/  BotRefuseOrder (TYPE_1__*) ; 
 int /*<<< orphan*/  BotSetTeamStatus (TYPE_1__*) ; 
 scalar_t__ CTF_RUSHBASE_TIME ; 
 scalar_t__ FloatTime () ; 
 scalar_t__ LTG_RUSHBASE ; 
 int /*<<< orphan*/  qfalse ; 

void BotCTFRetreatGoals(bot_state_t *bs) {
	//when carrying a flag in ctf the bot should rush to the base
	if (BotCTFCarryingFlag(bs)) {
		//if not already rushing to the base
		if (bs->ltgtype != LTG_RUSHBASE) {
			BotRefuseOrder(bs);
			bs->ltgtype = LTG_RUSHBASE;
			bs->teamgoal_time = FloatTime() + CTF_RUSHBASE_TIME;
			bs->rushbaseaway_time = 0;
			bs->decisionmaker = bs->client;
			bs->ordered = qfalse;
			BotSetTeamStatus(bs);
		}
	}
}
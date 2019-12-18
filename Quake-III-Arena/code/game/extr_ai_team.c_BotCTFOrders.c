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
struct TYPE_8__ {int redflagstatus; int blueflagstatus; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotCTFOrders_BothFlagsAtBase (TYPE_1__*) ; 
 int /*<<< orphan*/  BotCTFOrders_BothFlagsNotAtBase (TYPE_1__*) ; 
 int /*<<< orphan*/  BotCTFOrders_EnemyFlagNotAtBase (TYPE_1__*) ; 
 int /*<<< orphan*/  BotCTFOrders_FlagNotAtBase (TYPE_1__*) ; 
 scalar_t__ BotTeam (TYPE_1__*) ; 
 scalar_t__ TEAM_RED ; 

void BotCTFOrders(bot_state_t *bs) {
	int flagstatus;

	//
	if (BotTeam(bs) == TEAM_RED) flagstatus = bs->redflagstatus * 2 + bs->blueflagstatus;
	else flagstatus = bs->blueflagstatus * 2 + bs->redflagstatus;
	//
	switch(flagstatus) {
		case 0: BotCTFOrders_BothFlagsAtBase(bs); break;
		case 1: BotCTFOrders_EnemyFlagNotAtBase(bs); break;
		case 2: BotCTFOrders_FlagNotAtBase(bs); break;
		case 3: BotCTFOrders_BothFlagsNotAtBase(bs); break;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bot_state_t ;
typedef  int /*<<< orphan*/  bot_goal_t ;

/* Variables and functions */
 scalar_t__ BotTeam (int /*<<< orphan*/ *) ; 
 scalar_t__ TEAM_RED ; 
 int /*<<< orphan*/  ctf_blueflag ; 
 int /*<<< orphan*/  ctf_redflag ; 

bot_goal_t *BotEnemyFlag(bot_state_t *bs) {
	if (BotTeam(bs) == TEAM_RED) {
		return &ctf_blueflag;
	}
	else {
		return &ctf_redflag;
	}
}
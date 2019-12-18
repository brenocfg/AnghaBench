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

/* Variables and functions */
 int /*<<< orphan*/  BotPrintTeamGoal (int /*<<< orphan*/ *) ; 
 int BotTeamFlagCarrier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotVoiceChat_FollowMe (int /*<<< orphan*/ *,int,int) ; 

void BotVoiceChat_FollowFlagCarrier(bot_state_t *bs, int client, int mode) {
	int carrier;

	carrier = BotTeamFlagCarrier(bs);
	if (carrier >= 0)
		BotVoiceChat_FollowMe(bs, carrier, mode);
#ifdef DEBUG
	BotPrintTeamGoal(bs);
#endif //DEBUG
}
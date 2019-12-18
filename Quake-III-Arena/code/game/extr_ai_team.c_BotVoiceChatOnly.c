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
struct TYPE_3__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  trap_EA_Command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,...) ; 

void BotVoiceChatOnly(bot_state_t *bs, int toclient, char *voicechat) {
#ifdef MISSIONPACK
	if (toclient == -1)
		// voice only say team
		trap_EA_Command(bs->client, va("vosay_team %s", voicechat));
	else
		// voice only tell single player
		trap_EA_Command(bs->client, va("votell %d %s", toclient, voicechat));
#endif
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netname ;
struct TYPE_13__ {scalar_t__ askteamleader_time; scalar_t__ becometeamleader_time; scalar_t__ entergame_time; char* teamleader; int numteammates; scalar_t__ teamgiveorders_time; scalar_t__ lastflagcapture_time; void* forceorders; int /*<<< orphan*/  ctfstrategy; void* flagstatuschanged; int /*<<< orphan*/  client; int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  Bot1FCTFOrders (TYPE_1__*) ; 
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotCTFOrders (TYPE_1__*) ; 
 int /*<<< orphan*/  BotHarvesterOrders (TYPE_1__*) ; 
 int BotNumTeamMates (TYPE_1__*) ; 
 int /*<<< orphan*/  BotObeliskOrders (TYPE_1__*) ; 
 int /*<<< orphan*/  BotSayVoiceTeamOrder (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BotTeamOrders (TYPE_1__*) ; 
 int /*<<< orphan*/  BotValidTeamLeader (TYPE_1__*) ; 
 int /*<<< orphan*/  CHAT_TEAM ; 
 int /*<<< orphan*/  CTFS_AGRESSIVE ; 
 int /*<<< orphan*/  ClientName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  FindHumanTeamLeader (TYPE_1__*) ; 
 scalar_t__ FloatTime () ; 
#define  GT_1FCTF 132 
#define  GT_CTF 131 
#define  GT_HARVESTER 130 
#define  GT_OBELISK 129 
#define  GT_TEAM 128 
 int MAX_NETNAME ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  VOICECHAT_STARTLEADER ; 
 int gametype ; 
 void* qfalse ; 
 double random () ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BotTeamAI(bot_state_t *bs) {
	int numteammates;
	char netname[MAX_NETNAME];

	//
	if ( gametype < GT_TEAM  )
		return;
	// make sure we've got a valid team leader
	if (!BotValidTeamLeader(bs)) {
		//
		if (!FindHumanTeamLeader(bs)) {
			//
			if (!bs->askteamleader_time && !bs->becometeamleader_time) {
				if (bs->entergame_time + 10 > FloatTime()) {
					bs->askteamleader_time = FloatTime() + 5 + random() * 10;
				}
				else {
					bs->becometeamleader_time = FloatTime() + 5 + random() * 10;
				}
			}
			if (bs->askteamleader_time && bs->askteamleader_time < FloatTime()) {
				// if asked for a team leader and no response
				BotAI_BotInitialChat(bs, "whoisteamleader", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				bs->askteamleader_time = 0;
				bs->becometeamleader_time = FloatTime() + 8 + random() * 10;
			}
			if (bs->becometeamleader_time && bs->becometeamleader_time < FloatTime()) {
				BotAI_BotInitialChat(bs, "iamteamleader", NULL);
				trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
				BotSayVoiceTeamOrder(bs, -1, VOICECHAT_STARTLEADER);
				ClientName(bs->client, netname, sizeof(netname));
				strncpy(bs->teamleader, netname, sizeof(bs->teamleader));
				bs->teamleader[sizeof(bs->teamleader)] = '\0';
				bs->becometeamleader_time = 0;
			}
			return;
		}
	}
	bs->askteamleader_time = 0;
	bs->becometeamleader_time = 0;

	//return if this bot is NOT the team leader
	ClientName(bs->client, netname, sizeof(netname));
	if (Q_stricmp(netname, bs->teamleader) != 0) return;
	//
	numteammates = BotNumTeamMates(bs);
	//give orders
	switch(gametype) {
		case GT_TEAM:
		{
			if (bs->numteammates != numteammates || bs->forceorders) {
				bs->teamgiveorders_time = FloatTime();
				bs->numteammates = numteammates;
				bs->forceorders = qfalse;
			}
			//if it's time to give orders
			if (bs->teamgiveorders_time && bs->teamgiveorders_time < FloatTime() - 5) {
				BotTeamOrders(bs);
				//give orders again after 120 seconds
				bs->teamgiveorders_time = FloatTime() + 120;
			}
			break;
		}
		case GT_CTF:
		{
			//if the number of team mates changed or the flag status changed
			//or someone wants to know what to do
			if (bs->numteammates != numteammates || bs->flagstatuschanged || bs->forceorders) {
				bs->teamgiveorders_time = FloatTime();
				bs->numteammates = numteammates;
				bs->flagstatuschanged = qfalse;
				bs->forceorders = qfalse;
			}
			//if there were no flag captures the last 3 minutes
			if (bs->lastflagcapture_time < FloatTime() - 240) {
				bs->lastflagcapture_time = FloatTime();
				//randomly change the CTF strategy
				if (random() < 0.4) {
					bs->ctfstrategy ^= CTFS_AGRESSIVE;
					bs->teamgiveorders_time = FloatTime();
				}
			}
			//if it's time to give orders
			if (bs->teamgiveorders_time && bs->teamgiveorders_time < FloatTime() - 3) {
				BotCTFOrders(bs);
				//
				bs->teamgiveorders_time = 0;
			}
			break;
		}
#ifdef MISSIONPACK
		case GT_1FCTF:
		{
			if (bs->numteammates != numteammates || bs->flagstatuschanged || bs->forceorders) {
				bs->teamgiveorders_time = FloatTime();
				bs->numteammates = numteammates;
				bs->flagstatuschanged = qfalse;
				bs->forceorders = qfalse;
			}
			//if there were no flag captures the last 4 minutes
			if (bs->lastflagcapture_time < FloatTime() - 240) {
				bs->lastflagcapture_time = FloatTime();
				//randomly change the CTF strategy
				if (random() < 0.4) {
					bs->ctfstrategy ^= CTFS_AGRESSIVE;
					bs->teamgiveorders_time = FloatTime();
				}
			}
			//if it's time to give orders
			if (bs->teamgiveorders_time && bs->teamgiveorders_time < FloatTime() - 2) {
				Bot1FCTFOrders(bs);
				//
				bs->teamgiveorders_time = 0;
			}
			break;
		}
		case GT_OBELISK:
		{
			if (bs->numteammates != numteammates || bs->forceorders) {
				bs->teamgiveorders_time = FloatTime();
				bs->numteammates = numteammates;
				bs->forceorders = qfalse;
			}
			//if it's time to give orders
			if (bs->teamgiveorders_time && bs->teamgiveorders_time < FloatTime() - 5) {
				BotObeliskOrders(bs);
				//give orders again after 30 seconds
				bs->teamgiveorders_time = FloatTime() + 30;
			}
			break;
		}
		case GT_HARVESTER:
		{
			if (bs->numteammates != numteammates || bs->forceorders) {
				bs->teamgiveorders_time = FloatTime();
				bs->numteammates = numteammates;
				bs->forceorders = qfalse;
			}
			//if it's time to give orders
			if (bs->teamgiveorders_time && bs->teamgiveorders_time < FloatTime() - 5) {
				BotHarvesterOrders(bs);
				//give orders again after 30 seconds
				bs->teamgiveorders_time = FloatTime() + 30;
			}
			break;
		}
#endif
	}
}
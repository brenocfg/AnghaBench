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
typedef  int /*<<< orphan*/  netname ;
struct TYPE_3__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClientName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  Com_sprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  FloatTime () ; 
 int MAX_NETNAME ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/ * nodeswitch ; 
 size_t numnodeswitches ; 

void BotRecordNodeSwitch(bot_state_t *bs, char *node, char *str, char *s) {
	char netname[MAX_NETNAME];

	ClientName(bs->client, netname, sizeof(netname));
	Com_sprintf(nodeswitch[numnodeswitches], 144, "%s at %2.1f entered %s: %s from %s\n", netname, FloatTime(), node, str, s);
#ifdef DEBUG
	if (0) {
		BotAI_Print(PRT_MESSAGE, nodeswitch[numnodeswitches]);
	}
#endif //DEBUG
	numnodeswitches++;
}
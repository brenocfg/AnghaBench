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
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ClientName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  FloatTime () ; 
 int MAX_NETNAME ; 
 int /*<<< orphan*/  MAX_NODESWITCHES ; 
 int /*<<< orphan*/  PRT_FATAL ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 char** nodeswitch ; 
 int numnodeswitches ; 

void BotDumpNodeSwitches(bot_state_t *bs) {
	int i;
	char netname[MAX_NETNAME];

	ClientName(bs->client, netname, sizeof(netname));
	BotAI_Print(PRT_MESSAGE, "%s at %1.1f switched more than %d AI nodes\n", netname, FloatTime(), MAX_NODESWITCHES);
	for (i = 0; i < numnodeswitches; i++) {
		BotAI_Print(PRT_MESSAGE, nodeswitch[i]);
	}
	BotAI_Print(PRT_FATAL, "");
}
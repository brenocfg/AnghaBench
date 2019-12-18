#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  teamleader; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_5__ {int /*<<< orphan*/  inuse; } ;

/* Variables and functions */
 int ClientFromName (int /*<<< orphan*/ ) ; 
 TYPE_2__** botstates ; 
 int qfalse ; 
 int qtrue ; 

int BotTeamLeader(bot_state_t *bs) {
	int leader;

	leader = ClientFromName(bs->teamleader);
	if (leader < 0) return qfalse;
	if (!botstates[leader] || !botstates[leader]->inuse) return qfalse;
	return qtrue;
}
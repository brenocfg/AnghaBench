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
struct TYPE_3__ {int /*<<< orphan*/  teamleader; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int ClientFromName (int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int BotValidTeamLeader(bot_state_t *bs) {
	if (!strlen(bs->teamleader)) return qfalse;
	if (ClientFromName(bs->teamleader) == -1) return qfalse;
	return qtrue;
}
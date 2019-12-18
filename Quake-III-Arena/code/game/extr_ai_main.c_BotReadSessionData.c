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
typedef  int /*<<< orphan*/  s ;
struct TYPE_4__ {int /*<<< orphan*/ * maxs; int /*<<< orphan*/ * mins; int /*<<< orphan*/ * origin; int /*<<< orphan*/  number; int /*<<< orphan*/  iteminfo; int /*<<< orphan*/  flags; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  areanum; } ;
struct TYPE_5__ {TYPE_1__ lastgoal_teamgoal; int /*<<< orphan*/  lastgoal_teammate; int /*<<< orphan*/  lastgoal_ltgtype; int /*<<< orphan*/  lastgoal_decisionmaker; int /*<<< orphan*/  client; } ;
typedef  TYPE_2__ bot_state_t ;

/* Variables and functions */
 int MAX_STRING_CHARS ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char const*,char*,int) ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

void BotReadSessionData(bot_state_t *bs) {
	char	s[MAX_STRING_CHARS];
	const char	*var;

	var = va( "botsession%i", bs->client );
	trap_Cvar_VariableStringBuffer( var, s, sizeof(s) );

	sscanf(s,
			"%i %i %i %i %i %i %i %i"
			" %f %f %f"
			" %f %f %f"
			" %f %f %f",
		&bs->lastgoal_decisionmaker,
		&bs->lastgoal_ltgtype,
		&bs->lastgoal_teammate,
		&bs->lastgoal_teamgoal.areanum,
		&bs->lastgoal_teamgoal.entitynum,
		&bs->lastgoal_teamgoal.flags,
		&bs->lastgoal_teamgoal.iteminfo,
		&bs->lastgoal_teamgoal.number,
		&bs->lastgoal_teamgoal.origin[0],
		&bs->lastgoal_teamgoal.origin[1],
		&bs->lastgoal_teamgoal.origin[2],
		&bs->lastgoal_teamgoal.mins[0],
		&bs->lastgoal_teamgoal.mins[1],
		&bs->lastgoal_teamgoal.mins[2],
		&bs->lastgoal_teamgoal.maxs[0],
		&bs->lastgoal_teamgoal.maxs[1],
		&bs->lastgoal_teamgoal.maxs[2]
		);
}
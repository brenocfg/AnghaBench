#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_9__ {int /*<<< orphan*/  number; } ;
struct TYPE_10__ {TYPE_1__ s; int /*<<< orphan*/  client; int /*<<< orphan*/  inuse; } ;
typedef  TYPE_2__ gentity_t ;
struct TYPE_11__ {scalar_t__ integer; } ;

/* Variables and functions */
 int COLOR_CYAN ; 
 int COLOR_GREEN ; 
 int COLOR_MAGENTA ; 
 scalar_t__ GT_TOURNAMENT ; 
 int /*<<< orphan*/  OnSameTeam (TYPE_2__*,TYPE_2__*) ; 
 int SAY_TEAM ; 
 int SAY_TELL ; 
 int g_entities ; 
 TYPE_4__ g_gametype ; 
 int /*<<< orphan*/  trap_SendServerCommand (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static void G_VoiceTo( gentity_t *ent, gentity_t *other, int mode, const char *id, qboolean voiceonly ) {
	int color;
	char *cmd;

	if (!other) {
		return;
	}
	if (!other->inuse) {
		return;
	}
	if (!other->client) {
		return;
	}
	if ( mode == SAY_TEAM && !OnSameTeam(ent, other) ) {
		return;
	}
	// no chatting to players in tournements
	if ( (g_gametype.integer == GT_TOURNAMENT )) {
		return;
	}

	if (mode == SAY_TEAM) {
		color = COLOR_CYAN;
		cmd = "vtchat";
	}
	else if (mode == SAY_TELL) {
		color = COLOR_MAGENTA;
		cmd = "vtell";
	}
	else {
		color = COLOR_GREEN;
		cmd = "vchat";
	}

	trap_SendServerCommand( other-g_entities, va("%s %d %d %d %s", cmd, voiceonly, ent->s.number, color, id));
}
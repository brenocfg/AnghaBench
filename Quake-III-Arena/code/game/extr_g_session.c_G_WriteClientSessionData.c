#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  teamLeader; int /*<<< orphan*/  losses; int /*<<< orphan*/  wins; int /*<<< orphan*/  spectatorClient; int /*<<< orphan*/  spectatorState; int /*<<< orphan*/  spectatorTime; int /*<<< orphan*/  sessionTeam; } ;
struct TYPE_7__ {TYPE_1__ sess; } ;
typedef  TYPE_2__ gclient_t ;
struct TYPE_8__ {int clients; } ;

/* Variables and functions */
 TYPE_4__ level ; 
 int /*<<< orphan*/  trap_Cvar_Set (char const*,char const*) ; 
 char* va (char*,TYPE_2__*,...) ; 

void G_WriteClientSessionData( gclient_t *client ) {
	const char	*s;
	const char	*var;

	s = va("%i %i %i %i %i %i %i", 
		client->sess.sessionTeam,
		client->sess.spectatorTime,
		client->sess.spectatorState,
		client->sess.spectatorClient,
		client->sess.wins,
		client->sess.losses,
		client->sess.teamLeader
		);

	var = va( "session%i", client - level.clients );

	trap_Cvar_Set( var, s );
}
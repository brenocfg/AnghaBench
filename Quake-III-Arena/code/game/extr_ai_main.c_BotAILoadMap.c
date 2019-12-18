#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ vmCvar_t ;
struct TYPE_6__ {int setupcount; scalar_t__ inuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotResetState (TYPE_3__*) ; 
 int /*<<< orphan*/  BotSetupDeathmatchAI () ; 
 int CVAR_ROM ; 
 int CVAR_SERVERINFO ; 
 int MAX_CLIENTS ; 
 TYPE_3__** botstates ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_BotLibLoadMap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_Register (TYPE_1__*,char*,char*,int) ; 

int BotAILoadMap( int restart ) {
	int			i;
	vmCvar_t	mapname;

	if (!restart) {
		trap_Cvar_Register( &mapname, "mapname", "", CVAR_SERVERINFO | CVAR_ROM );
		trap_BotLibLoadMap( mapname.string );
	}

	for (i = 0; i < MAX_CLIENTS; i++) {
		if (botstates[i] && botstates[i]->inuse) {
			BotResetState( botstates[i] );
			botstates[i]->setupcount = 4;
		}
	}

	BotSetupDeathmatchAI();

	return qtrue;
}
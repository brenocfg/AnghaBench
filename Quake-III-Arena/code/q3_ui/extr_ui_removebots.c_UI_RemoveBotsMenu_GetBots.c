#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
struct TYPE_2__ {size_t numBots; int* botClientNums; } ;

/* Variables and functions */
 scalar_t__ CS_PLAYERS ; 
 scalar_t__ CS_SERVERINFO ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 int atoi (int /*<<< orphan*/ ) ; 
 TYPE_1__ removeBotsMenuInfo ; 
 int /*<<< orphan*/  trap_GetConfigString (scalar_t__,char*,int) ; 

__attribute__((used)) static void UI_RemoveBotsMenu_GetBots( void ) {
	int		numPlayers;
	int		isBot;
	int		n;
	char	info[MAX_INFO_STRING];

	trap_GetConfigString( CS_SERVERINFO, info, sizeof(info) );
	numPlayers = atoi( Info_ValueForKey( info, "sv_maxclients" ) );
	removeBotsMenuInfo.numBots = 0;

	for( n = 0; n < numPlayers; n++ ) {
		trap_GetConfigString( CS_PLAYERS + n, info, MAX_INFO_STRING );

		isBot = atoi( Info_ValueForKey( info, "skill" ) );
		if( !isBot ) {
			continue;
		}

		removeBotsMenuInfo.botClientNums[removeBotsMenuInfo.numBots] = n;
		removeBotsMenuInfo.numBots++;
	}
}
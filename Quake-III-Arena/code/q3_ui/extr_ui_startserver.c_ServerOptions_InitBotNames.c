#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bots ;
struct TYPE_4__ {scalar_t__ gametype; char** playerNameBuffers; TYPE_1__* playerType; int /*<<< orphan*/  mapnamebuffer; } ;
struct TYPE_3__ {int curvalue; } ;

/* Variables and functions */
 scalar_t__ GT_TEAM ; 
 char* Info_ValueForKey (char const*,char*) ; 
 int MAX_INFO_STRING ; 
 int PLAYER_SLOTS ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 char* UI_GetArenaInfoByMap (int /*<<< orphan*/ ) ; 
 char* UI_GetBotInfoByName (char*) ; 
 TYPE_2__ s_serveroptions ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void ServerOptions_InitBotNames( void ) {
	int			count;
	int			n;
	const char	*arenaInfo;
	const char	*botInfo;
	char		*p;
	char		*bot;
	char		bots[MAX_INFO_STRING];

	if( s_serveroptions.gametype >= GT_TEAM ) {
		Q_strncpyz( s_serveroptions.playerNameBuffers[1], "grunt", 16 );
		Q_strncpyz( s_serveroptions.playerNameBuffers[2], "major", 16 );
		if( s_serveroptions.gametype == GT_TEAM ) {
			Q_strncpyz( s_serveroptions.playerNameBuffers[3], "visor", 16 );
		}
		else {
			s_serveroptions.playerType[3].curvalue = 2;
		}
		s_serveroptions.playerType[4].curvalue = 2;
		s_serveroptions.playerType[5].curvalue = 2;

		Q_strncpyz( s_serveroptions.playerNameBuffers[6], "sarge", 16 );
		Q_strncpyz( s_serveroptions.playerNameBuffers[7], "grunt", 16 );
		Q_strncpyz( s_serveroptions.playerNameBuffers[8], "major", 16 );
		if( s_serveroptions.gametype == GT_TEAM ) {
			Q_strncpyz( s_serveroptions.playerNameBuffers[9], "visor", 16 );
		}
		else {
			s_serveroptions.playerType[9].curvalue = 2;
		}
		s_serveroptions.playerType[10].curvalue = 2;
		s_serveroptions.playerType[11].curvalue = 2;

		return;
	}

	count = 1;	// skip the first slot, reserved for a human

	// get info for this map
	arenaInfo = UI_GetArenaInfoByMap( s_serveroptions.mapnamebuffer );

	// get the bot info - we'll seed with them if any are listed
	Q_strncpyz( bots, Info_ValueForKey( arenaInfo, "bots" ), sizeof(bots) );
	p = &bots[0];
	while( *p && count < PLAYER_SLOTS ) {
		//skip spaces
		while( *p && *p == ' ' ) {
			p++;
		}
		if( !p ) {
			break;
		}

		// mark start of bot name
		bot = p;

		// skip until space of null
		while( *p && *p != ' ' ) {
			p++;
		}
		if( *p ) {
			*p++ = 0;
		}

		botInfo = UI_GetBotInfoByName( bot );
		bot = Info_ValueForKey( botInfo, "name" );

		Q_strncpyz( s_serveroptions.playerNameBuffers[count], bot, sizeof(s_serveroptions.playerNameBuffers[count]) );
		count++;
	}

	// set the rest of the bot slots to "---"
	for( n = count; n < PLAYER_SLOTS; n++ ) {
		strcpy( s_serveroptions.playerNameBuffers[n], "--------" );
	}

	// pad up to #8 as open slots
	for( ;count < 8; count++ ) {
		s_serveroptions.playerType[count].curvalue = 0;
	}

	// close off the rest by default
	for( ;count < PLAYER_SLOTS; count++ ) {
		if( s_serveroptions.playerType[count].curvalue == 1 ) {
			s_serveroptions.playerType[count].curvalue = 2;
		}
	}
}
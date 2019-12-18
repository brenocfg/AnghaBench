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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ refreshtime; scalar_t__ nextpingtime; size_t numqueriedservers; size_t numfavoriteaddresses; size_t currentping; char** favoriteaddresses; TYPE_1__* pinglist; } ;
struct TYPE_5__ {scalar_t__ realtime; } ;
struct TYPE_4__ {char* adrstr; int start; } ;

/* Variables and functions */
 scalar_t__ AS_FAVORITES ; 
 scalar_t__ AS_LOCAL ; 
 int /*<<< orphan*/  ArenaServers_Insert (char*,char*,int) ; 
 int ArenaServers_MaxPing () ; 
 int /*<<< orphan*/  ArenaServers_StopRefresh () ; 
 int /*<<< orphan*/  ArenaServers_UpdateMenu () ; 
 int /*<<< orphan*/  EXEC_NOW ; 
 int MAX_ADDRESSLENGTH ; 
 int MAX_INFO_STRING ; 
 int MAX_PINGREQUESTS ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 TYPE_3__ g_arenaservers ; 
 scalar_t__ g_servertype ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_LAN_ClearPing (int) ; 
 int /*<<< orphan*/  trap_LAN_GetPing (int,char*,int,int*) ; 
 int /*<<< orphan*/  trap_LAN_GetPingInfo (int,char*,int) ; 
 int trap_LAN_GetPingQueueCount () ; 
 int /*<<< orphan*/  trap_LAN_GetServerAddressString (scalar_t__,size_t,char*,int) ; 
 scalar_t__ trap_LAN_GetServerCount (scalar_t__) ; 
 TYPE_2__ uis ; 
 int /*<<< orphan*/  va (char*,char*) ; 

__attribute__((used)) static void ArenaServers_DoRefresh( void )
{
	int		i;
	int		j;
	int		time;
	int		maxPing;
	char	adrstr[MAX_ADDRESSLENGTH];
	char	info[MAX_INFO_STRING];

	if (uis.realtime < g_arenaservers.refreshtime)
	{
	  if (g_servertype != AS_FAVORITES) {
			if (g_servertype == AS_LOCAL) {
				if (!trap_LAN_GetServerCount(g_servertype)) {
					return;
				}
			}
			if (trap_LAN_GetServerCount(g_servertype) < 0) {
			  // still waiting for response
			  return;
			}
	  }
	}

	if (uis.realtime < g_arenaservers.nextpingtime)
	{
		// wait for time trigger
		return;
	}

	// trigger at 10Hz intervals
	g_arenaservers.nextpingtime = uis.realtime + 10;

	// process ping results
	maxPing = ArenaServers_MaxPing();
	for (i=0; i<MAX_PINGREQUESTS; i++)
	{
		trap_LAN_GetPing( i, adrstr, MAX_ADDRESSLENGTH, &time );
		if (!adrstr[0])
		{
			// ignore empty or pending pings
			continue;
		}

		// find ping result in our local list
		for (j=0; j<MAX_PINGREQUESTS; j++)
			if (!Q_stricmp( adrstr, g_arenaservers.pinglist[j].adrstr ))
				break;

		if (j < MAX_PINGREQUESTS)
		{
			// found it
			if (!time)
			{
				time = uis.realtime - g_arenaservers.pinglist[j].start;
				if (time < maxPing)
				{
					// still waiting
					continue;
				}
			}

			if (time > maxPing)
			{
				// stale it out
				info[0] = '\0';
				time    = maxPing;
			}
			else
			{
				trap_LAN_GetPingInfo( i, info, MAX_INFO_STRING );
			}

			// insert ping results
			ArenaServers_Insert( adrstr, info, time );

			// clear this query from internal list
			g_arenaservers.pinglist[j].adrstr[0] = '\0';
   		}

		// clear this query from external list
		trap_LAN_ClearPing( i );
	}

	// get results of servers query
	// counts can increase as servers respond
	if (g_servertype == AS_FAVORITES) {
	  g_arenaservers.numqueriedservers = g_arenaservers.numfavoriteaddresses;
	} else {
	  g_arenaservers.numqueriedservers = trap_LAN_GetServerCount(g_servertype);
	}

//	if (g_arenaservers.numqueriedservers > g_arenaservers.maxservers)
//		g_arenaservers.numqueriedservers = g_arenaservers.maxservers;

	// send ping requests in reasonable bursts
	// iterate ping through all found servers
	for (i=0; i<MAX_PINGREQUESTS && g_arenaservers.currentping < g_arenaservers.numqueriedservers; i++)
	{
		if (trap_LAN_GetPingQueueCount() >= MAX_PINGREQUESTS)
		{
			// ping queue is full
			break;
		}

		// find empty slot
		for (j=0; j<MAX_PINGREQUESTS; j++)
			if (!g_arenaservers.pinglist[j].adrstr[0])
				break;

		if (j >= MAX_PINGREQUESTS)
			// no empty slots available yet - wait for timeout
			break;

		// get an address to ping

		if (g_servertype == AS_FAVORITES) {
		  strcpy( adrstr, g_arenaservers.favoriteaddresses[g_arenaservers.currentping] ); 		
		} else {
		  trap_LAN_GetServerAddressString(g_servertype, g_arenaservers.currentping, adrstr, MAX_ADDRESSLENGTH );
		}

		strcpy( g_arenaservers.pinglist[j].adrstr, adrstr );
		g_arenaservers.pinglist[j].start = uis.realtime;

		trap_Cmd_ExecuteText( EXEC_NOW, va( "ping %s\n", adrstr )  );
		
		// advance to next server
		g_arenaservers.currentping++;
	}

	if (!trap_LAN_GetPingQueueCount())
	{
		// all pings completed
		ArenaServers_StopRefresh();
		return;
	}

	// update the user interface with ping status
	ArenaServers_UpdateMenu();
}
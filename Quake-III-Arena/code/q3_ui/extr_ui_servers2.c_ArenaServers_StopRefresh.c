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
typedef  int /*<<< orphan*/  servernode_t ;
struct TYPE_2__ {scalar_t__ numqueriedservers; scalar_t__ currentping; scalar_t__* numservers; int /*<<< orphan*/  serverlist; scalar_t__ refreshservers; } ;

/* Variables and functions */
 scalar_t__ AS_FAVORITES ; 
 int /*<<< orphan*/  ArenaServers_Compare ; 
 int /*<<< orphan*/  ArenaServers_InsertFavorites () ; 
 int /*<<< orphan*/  ArenaServers_UpdateMenu () ; 
 TYPE_1__ g_arenaservers ; 
 scalar_t__ g_servertype ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ArenaServers_StopRefresh( void )
{
	if (!g_arenaservers.refreshservers)
		// not currently refreshing
		return;

	g_arenaservers.refreshservers = qfalse;

	if (g_servertype == AS_FAVORITES)
	{
		// nonresponsive favorites must be shown
		ArenaServers_InsertFavorites();
	}

	// final tally
	if (g_arenaservers.numqueriedservers >= 0)
	{
		g_arenaservers.currentping       = *g_arenaservers.numservers;
		g_arenaservers.numqueriedservers = *g_arenaservers.numservers; 
	}
	
	// sort
	qsort( g_arenaservers.serverlist, *g_arenaservers.numservers, sizeof( servernode_t ), ArenaServers_Compare);

	ArenaServers_UpdateMenu();
}
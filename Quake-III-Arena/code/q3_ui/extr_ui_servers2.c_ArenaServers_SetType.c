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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ generic; } ;
struct TYPE_8__ {TYPE_3__ status; scalar_t__* numservers; scalar_t__ numqueriedservers; scalar_t__ currentping; void* maxservers; int /*<<< orphan*/  serverlist; TYPE_2__ remove; } ;

/* Variables and functions */
#define  AS_FAVORITES 131 
#define  AS_GLOBAL 130 
#define  AS_LOCAL 129 
#define  AS_MPLAYER 128 
 int /*<<< orphan*/  ArenaServers_StartRefresh () ; 
 int /*<<< orphan*/  ArenaServers_UpdateMenu () ; 
 void* MAX_FAVORITESERVERS ; 
 void* MAX_GLOBALSERVERS ; 
 void* MAX_LOCALSERVERS ; 
 int QMF_HIDDEN ; 
 int QMF_INACTIVE ; 
 TYPE_4__ g_arenaservers ; 
 int /*<<< orphan*/  g_favoriteserverlist ; 
 int /*<<< orphan*/  g_globalserverlist ; 
 int /*<<< orphan*/  g_localserverlist ; 
 int /*<<< orphan*/  g_mplayerserverlist ; 
 scalar_t__ g_numfavoriteservers ; 
 scalar_t__ g_numglobalservers ; 
 scalar_t__ g_numlocalservers ; 
 scalar_t__ g_nummplayerservers ; 
 int g_servertype ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void ArenaServers_SetType( int type )
{
	if (g_servertype == type)
		return;

	g_servertype = type;

	switch( type ) {
	default:
	case AS_LOCAL:
		g_arenaservers.remove.generic.flags |= (QMF_INACTIVE|QMF_HIDDEN);
		g_arenaservers.serverlist = g_localserverlist;
		g_arenaservers.numservers = &g_numlocalservers;
		g_arenaservers.maxservers = MAX_LOCALSERVERS;
		break;

	case AS_GLOBAL:
		g_arenaservers.remove.generic.flags |= (QMF_INACTIVE|QMF_HIDDEN);
		g_arenaservers.serverlist = g_globalserverlist;
		g_arenaservers.numservers = &g_numglobalservers;
		g_arenaservers.maxservers = MAX_GLOBALSERVERS;
		break;

	case AS_FAVORITES:
		g_arenaservers.remove.generic.flags &= ~(QMF_INACTIVE|QMF_HIDDEN);
		g_arenaservers.serverlist = g_favoriteserverlist;
		g_arenaservers.numservers = &g_numfavoriteservers;
		g_arenaservers.maxservers = MAX_FAVORITESERVERS;
		break;

	case AS_MPLAYER:
		g_arenaservers.remove.generic.flags |= (QMF_INACTIVE|QMF_HIDDEN);
		g_arenaservers.serverlist = g_mplayerserverlist;
		g_arenaservers.numservers = &g_nummplayerservers;
		g_arenaservers.maxservers = MAX_GLOBALSERVERS;
		break;
		
	}

	if( !*g_arenaservers.numservers ) {
		ArenaServers_StartRefresh();
	}
	else {
		// avoid slow operation, use existing results
		g_arenaservers.currentping       = *g_arenaservers.numservers;
		g_arenaservers.numqueriedservers = *g_arenaservers.numservers; 
		ArenaServers_UpdateMenu();
	}
	strcpy(g_arenaservers.status.string,"hit refresh to update");
}
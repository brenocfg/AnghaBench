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
typedef  int qboolean ;
struct TYPE_8__ {scalar_t__ integer; } ;
struct TYPE_7__ {int numPlayingClients; scalar_t__* teamScores; size_t* sortedClients; TYPE_1__* clients; } ;
struct TYPE_6__ {int* persistant; } ;
struct TYPE_5__ {TYPE_2__ ps; } ;

/* Variables and functions */
 scalar_t__ GT_TEAM ; 
 size_t PERS_SCORE ; 
 size_t TEAM_BLUE ; 
 size_t TEAM_RED ; 
 TYPE_4__ g_gametype ; 
 TYPE_3__ level ; 
 int qfalse ; 

qboolean ScoreIsTied( void ) {
	int		a, b;

	if ( level.numPlayingClients < 2 ) {
		return qfalse;
	}
	
	if ( g_gametype.integer >= GT_TEAM ) {
		return level.teamScores[TEAM_RED] == level.teamScores[TEAM_BLUE];
	}

	a = level.clients[level.sortedClients[0]].ps.persistant[PERS_SCORE];
	b = level.clients[level.sortedClients[1]].ps.persistant[PERS_SCORE];

	return a == b;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* mo; } ;
struct TYPE_7__ {int type; } ;
struct TYPE_6__ {int /*<<< orphan*/ * player; } ;

/* Variables and functions */
 scalar_t__ G_CheckSpot (int,TYPE_2__*) ; 
 int /*<<< orphan*/  G_DeathMatchSpawnPlayer (int) ; 
 int MAXPLAYERS ; 
 int /*<<< orphan*/  P_SpawnPlayer (TYPE_2__*) ; 
 scalar_t__ deathmatch ; 
 int /*<<< orphan*/  ga_loadlevel ; 
 int /*<<< orphan*/  gameaction ; 
 int /*<<< orphan*/  netgame ; 
 TYPE_3__* players ; 
 TYPE_2__* playerstarts ; 

void G_DoReborn (int playernum) 
{ 
    int                             i; 
	 
    if (!netgame)
    {
	// reload the level from scratch
	gameaction = ga_loadlevel;  
    }
    else 
    {
	// respawn at the start

	// first dissasociate the corpse 
	players[playernum].mo->player = NULL;   
		 
	// spawn at random spot if in death match 
	if (deathmatch) 
	{ 
	    G_DeathMatchSpawnPlayer (playernum); 
	    return; 
	} 
		 
	if (G_CheckSpot (playernum, &playerstarts[playernum]) ) 
	{ 
	    P_SpawnPlayer (&playerstarts[playernum]); 
	    return; 
	}
	
	// try to spawn at one of the other players spots 
	for (i=0 ; i<MAXPLAYERS ; i++)
	{
	    if (G_CheckSpot (playernum, &playerstarts[i]) ) 
	    { 
		playerstarts[i].type = playernum+1;	// fake as other player 
		P_SpawnPlayer (&playerstarts[i]); 
		playerstarts[i].type = i+1;		// restore 
		return; 
	    }	    
	    // he's going to be inside something.  Too bad.
	}
	P_SpawnPlayer (&playerstarts[playernum]); 
    } 
}
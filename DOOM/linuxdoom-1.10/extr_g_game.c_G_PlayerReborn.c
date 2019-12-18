#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* frags; int killcount; int itemcount; int secretcount; int usedown; int attackdown; size_t readyweapon; size_t pendingweapon; int* weaponowned; int* ammo; int /*<<< orphan*/ * maxammo; int /*<<< orphan*/  health; int /*<<< orphan*/  playerstate; } ;
typedef  TYPE_1__ player_t ;
typedef  int /*<<< orphan*/  frags ;

/* Variables and functions */
 int /*<<< orphan*/  MAXHEALTH ; 
 int MAXPLAYERS ; 
 int NUMAMMO ; 
 int /*<<< orphan*/  PST_LIVE ; 
 size_t am_clip ; 
 int /*<<< orphan*/ * maxammo ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* players ; 
 size_t wp_fist ; 
 size_t wp_pistol ; 

void G_PlayerReborn (int player) 
{ 
    player_t*	p; 
    int		i; 
    int		frags[MAXPLAYERS]; 
    int		killcount;
    int		itemcount;
    int		secretcount; 
	 
    memcpy (frags,players[player].frags,sizeof(frags)); 
    killcount = players[player].killcount; 
    itemcount = players[player].itemcount; 
    secretcount = players[player].secretcount; 
	 
    p = &players[player]; 
    memset (p, 0, sizeof(*p)); 
 
    memcpy (players[player].frags, frags, sizeof(players[player].frags)); 
    players[player].killcount = killcount; 
    players[player].itemcount = itemcount; 
    players[player].secretcount = secretcount; 
 
    p->usedown = p->attackdown = true;	// don't do anything immediately 
    p->playerstate = PST_LIVE;       
    p->health = MAXHEALTH; 
    p->readyweapon = p->pendingweapon = wp_pistol; 
    p->weaponowned[wp_fist] = true; 
    p->weaponowned[wp_pistol] = true; 
    p->ammo[am_clip] = 50; 
	 
    for (i=0 ; i<NUMAMMO ; i++) 
	p->maxammo[i] = maxammo[i]; 
		 
}
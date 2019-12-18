#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  G_InitNew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ consoleplayer ; 
 int /*<<< orphan*/  d_episode ; 
 int /*<<< orphan*/  d_map ; 
 int /*<<< orphan*/  d_skill ; 
 int deathmatch ; 
 int demoplayback ; 
 int fastparm ; 
 int /*<<< orphan*/  ga_nothing ; 
 int /*<<< orphan*/  gameaction ; 
 int netdemo ; 
 int netgame ; 
 int nomonsters ; 
 scalar_t__* playeringame ; 
 int respawnparm ; 

void G_DoNewGame (void) 
{
    demoplayback = false; 
    netdemo = false;
    netgame = false;
    deathmatch = false;
    playeringame[1] = playeringame[2] = playeringame[3] = 0;
    respawnparm = false;
    fastparm = false;
    nomonsters = false;
    consoleplayer = 0;
    G_InitNew (d_skill, d_episode, d_map); 
    gameaction = ga_nothing; 
}
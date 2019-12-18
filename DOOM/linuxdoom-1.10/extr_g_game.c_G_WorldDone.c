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
struct TYPE_2__ {int didsecret; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_StartFinale () ; 
 scalar_t__ commercial ; 
 size_t consoleplayer ; 
 int /*<<< orphan*/  ga_worlddone ; 
 int /*<<< orphan*/  gameaction ; 
 int gamemap ; 
 scalar_t__ gamemode ; 
 TYPE_1__* players ; 
 scalar_t__ secretexit ; 

void G_WorldDone (void) 
{ 
    gameaction = ga_worlddone; 

    if (secretexit) 
	players[consoleplayer].didsecret = true; 

    if ( gamemode == commercial )
    {
	switch (gamemap)
	{
	  case 15:
	  case 31:
	    if (!secretexit)
		break;
	  case 6:
	  case 11:
	  case 20:
	  case 30:
	    F_StartFinale ();
	    break;
	}
    }
}
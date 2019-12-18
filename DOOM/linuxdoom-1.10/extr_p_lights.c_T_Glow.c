#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int direction; TYPE_1__* sector; int /*<<< orphan*/  maxlight; int /*<<< orphan*/  minlight; } ;
typedef  TYPE_2__ glow_t ;
struct TYPE_4__ {int /*<<< orphan*/  lightlevel; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOWSPEED ; 

void T_Glow(glow_t*	g)
{
    switch(g->direction)
    {
      case -1:
	// DOWN
	g->sector->lightlevel -= GLOWSPEED;
	if (g->sector->lightlevel <= g->minlight)
	{
	    g->sector->lightlevel += GLOWSPEED;
	    g->direction = 1;
	}
	break;
	
      case 1:
	// UP
	g->sector->lightlevel += GLOWSPEED;
	if (g->sector->lightlevel >= g->maxlight)
	{
	    g->sector->lightlevel -= GLOWSPEED;
	    g->direction = -1;
	}
	break;
    }
}
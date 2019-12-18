#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* mo; scalar_t__* powers; } ;
typedef  TYPE_2__ player_t ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  angle; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_drawLineCharacter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  BROWNS 131 
#define  GRAYS 130 
#define  GREENS 129 
 int MAXPLAYERS ; 
 int /*<<< orphan*/  NUMCHEATPLYRLINES ; 
 int /*<<< orphan*/  NUMPLYRLINES ; 
#define  REDS 128 
 int WHITE ; 
 int /*<<< orphan*/  cheat_player_arrow ; 
 scalar_t__ cheating ; 
 scalar_t__ deathmatch ; 
 int /*<<< orphan*/  netgame ; 
 int /*<<< orphan*/  player_arrow ; 
 int /*<<< orphan*/ * playeringame ; 
 TYPE_2__* players ; 
 TYPE_2__* plr ; 
 size_t pw_invisibility ; 
 int /*<<< orphan*/  singledemo ; 

void AM_drawPlayers(void)
{
    int		i;
    player_t*	p;
    static int 	their_colors[] = { GREENS, GRAYS, BROWNS, REDS };
    int		their_color = -1;
    int		color;

    if (!netgame)
    {
	if (cheating)
	    AM_drawLineCharacter
		(cheat_player_arrow, NUMCHEATPLYRLINES, 0,
		 plr->mo->angle, WHITE, plr->mo->x, plr->mo->y);
	else
	    AM_drawLineCharacter
		(player_arrow, NUMPLYRLINES, 0, plr->mo->angle,
		 WHITE, plr->mo->x, plr->mo->y);
	return;
    }

    for (i=0;i<MAXPLAYERS;i++)
    {
	their_color++;
	p = &players[i];

	if ( (deathmatch && !singledemo) && p != plr)
	    continue;

	if (!playeringame[i])
	    continue;

	if (p->powers[pw_invisibility])
	    color = 246; // *close* to black
	else
	    color = their_colors[their_color];
	
	AM_drawLineCharacter
	    (player_arrow, NUMPLYRLINES, 0, p->mo->angle,
	     color, p->mo->x, p->mo->y);
    }

}
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
typedef  int /*<<< orphan*/  player_t ;
struct TYPE_5__ {TYPE_1__* psprites; int /*<<< orphan*/ * attacker; int /*<<< orphan*/ * message; int /*<<< orphan*/ * mo; } ;
struct TYPE_4__ {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int MAXPLAYERS ; 
 int NUMPSPRITES ; 
 int /*<<< orphan*/  PADSAVEP () ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/ * playeringame ; 
 TYPE_2__* players ; 
 int save_p ; 
 int /*<<< orphan*/ * states ; 

void P_UnArchivePlayers (void)
{
    int		i;
    int		j;
	
    for (i=0 ; i<MAXPLAYERS ; i++)
    {
	if (!playeringame[i])
	    continue;
	
	PADSAVEP();

	memcpy (&players[i],save_p, sizeof(player_t));
	save_p += sizeof(player_t);
	
	// will be set when unarc thinker
	players[i].mo = NULL;	
	players[i].message = NULL;
	players[i].attacker = NULL;

	for (j=0 ; j<NUMPSPRITES ; j++)
	{
	    if (players[i]. psprites[j].state)
	    {
		players[i]. psprites[j].state 
		    = &states[ (int)players[i].psprites[j].state ];
	    }
	}
    }
}
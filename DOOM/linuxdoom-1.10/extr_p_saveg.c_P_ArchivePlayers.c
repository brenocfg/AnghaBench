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
typedef  int /*<<< orphan*/  state_t ;
struct TYPE_5__ {TYPE_1__* psprites; } ;
typedef  TYPE_2__ player_t ;
struct TYPE_4__ {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int MAXPLAYERS ; 
 int NUMPSPRITES ; 
 int /*<<< orphan*/  PADSAVEP () ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * playeringame ; 
 int /*<<< orphan*/ * players ; 
 scalar_t__ save_p ; 
 int states ; 

void P_ArchivePlayers (void)
{
    int		i;
    int		j;
    player_t*	dest;
		
    for (i=0 ; i<MAXPLAYERS ; i++)
    {
	if (!playeringame[i])
	    continue;
	
	PADSAVEP();

	dest = (player_t *)save_p;
	memcpy (dest,&players[i],sizeof(player_t));
	save_p += sizeof(player_t);
	for (j=0 ; j<NUMPSPRITES ; j++)
	{
	    if (dest->psprites[j].state)
	    {
		dest->psprites[j].state 
		    = (state_t *)(dest->psprites[j].state-states);
	    }
	}
    }
}
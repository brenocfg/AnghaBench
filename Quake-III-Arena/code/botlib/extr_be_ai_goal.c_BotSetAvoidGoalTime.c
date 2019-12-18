#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int number; size_t iteminfo; struct TYPE_6__* next; } ;
typedef  TYPE_2__ levelitem_t ;
typedef  int /*<<< orphan*/  bot_goalstate_t ;
struct TYPE_7__ {TYPE_1__* iteminfo; } ;
struct TYPE_5__ {float respawntime; } ;

/* Variables and functions */
 float AVOID_DEFAULT_TIME ; 
 float AVOID_MINIMUM_TIME ; 
 int /*<<< orphan*/  BotAddToAvoidGoals (int /*<<< orphan*/ *,int,float) ; 
 int /*<<< orphan*/ * BotGoalStateFromHandle (int) ; 
 TYPE_4__* itemconfig ; 
 TYPE_2__* levelitems ; 

void BotSetAvoidGoalTime(int goalstate, int number, float avoidtime)
{
	bot_goalstate_t *gs;
	levelitem_t *li;

	gs = BotGoalStateFromHandle(goalstate);
	if (!gs)
		return;
	if (avoidtime < 0)
	{
		if (!itemconfig)
			return;
		//
		for (li = levelitems; li; li = li->next)
		{
			if (li->number == number)
			{
				avoidtime = itemconfig->iteminfo[li->iteminfo].respawntime;
				if (!avoidtime)
					avoidtime = AVOID_DEFAULT_TIME;
				if (avoidtime < AVOID_MINIMUM_TIME)
					avoidtime = AVOID_MINIMUM_TIME;
				BotAddToAvoidGoals(gs, number, avoidtime);
				return;
			} //end for
		} //end for
		return;
	} //end if
	else
	{
		BotAddToAvoidGoals(gs, number, avoidtime);
	} //end else
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; struct TYPE_5__* next; struct TYPE_5__* firststring; } ;
typedef  TYPE_1__ bot_matchstring_t ;
typedef  TYPE_1__ bot_matchpiece_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 scalar_t__ MT_STRING ; 

void BotFreeMatchPieces(bot_matchpiece_t *matchpieces)
{
	bot_matchpiece_t *mp, *nextmp;
	bot_matchstring_t *ms, *nextms;

	for (mp = matchpieces; mp; mp = nextmp)
	{
		nextmp = mp->next;
		if (mp->type == MT_STRING)
		{
			for (ms = mp->firststring; ms; ms = nextms)
			{
				nextms = ms->next;
				FreeMemory(ms);
			} //end for
		} //end if
		FreeMemory(mp);
	} //end for
}
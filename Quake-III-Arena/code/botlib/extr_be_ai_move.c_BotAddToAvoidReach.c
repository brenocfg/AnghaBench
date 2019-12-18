#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* avoidreach; scalar_t__* avoidreachtimes; int* avoidreachtries; } ;
typedef  TYPE_1__ bot_movestate_t ;

/* Variables and functions */
 scalar_t__ AAS_Time () ; 
 int MAX_AVOIDREACH ; 

void BotAddToAvoidReach(bot_movestate_t *ms, int number, float avoidtime)
{
	int i;

	for (i = 0; i < MAX_AVOIDREACH; i++)
	{
		if (ms->avoidreach[i] == number)
		{
			if (ms->avoidreachtimes[i] > AAS_Time()) ms->avoidreachtries[i]++;
			else ms->avoidreachtries[i] = 1;
			ms->avoidreachtimes[i] = AAS_Time() + avoidtime;
			return;
		} //end if
	} //end for
	//add the reachability to the reachabilities to avoid for a while
	for (i = 0; i < MAX_AVOIDREACH; i++)
	{
		if (ms->avoidreachtimes[i] < AAS_Time())
		{
			ms->avoidreach[i] = number;
			ms->avoidreachtimes[i] = AAS_Time() + avoidtime;
			ms->avoidreachtries[i] = 1;
			return;
		} //end if
	} //end for
}
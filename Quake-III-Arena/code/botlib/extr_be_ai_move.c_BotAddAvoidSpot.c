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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {size_t numavoidspots; TYPE_1__* avoidspots; } ;
typedef  TYPE_2__ bot_movestate_t ;
struct TYPE_4__ {float radius; int type; int /*<<< orphan*/  origin; } ;

/* Variables and functions */
 int AVOID_CLEAR ; 
 TYPE_2__* BotMoveStateFromHandle (int) ; 
 size_t MAX_AVOIDSPOTS ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BotAddAvoidSpot(int movestate, vec3_t origin, float radius, int type)
{
	bot_movestate_t *ms;

	ms = BotMoveStateFromHandle(movestate);
	if (!ms) return;
	if (type == AVOID_CLEAR)
	{
		ms->numavoidspots = 0;
		return;
	} //end if

	if (ms->numavoidspots >= MAX_AVOIDSPOTS)
		return;
	VectorCopy(origin, ms->avoidspots[ms->numavoidspots].origin);
	ms->avoidspots[ms->numavoidspots].radius = radius;
	ms->avoidspots[ms->numavoidspots].type = type;
	ms->numavoidspots++;
}
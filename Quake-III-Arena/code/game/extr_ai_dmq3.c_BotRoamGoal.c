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
typedef  scalar_t__* vec3_t ;
struct TYPE_5__ {float fraction; int /*<<< orphan*/ * endpos; int /*<<< orphan*/  startsolid; } ;
typedef  TYPE_1__ bsp_trace_t ;
struct TYPE_6__ {int /*<<< orphan*/  entitynum; scalar_t__* origin; } ;
typedef  TYPE_2__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Trace (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int /*<<< orphan*/  MASK_SOLID ; 
 int /*<<< orphan*/  VectorAdd (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 float VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  VectorScale (scalar_t__*,float,scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int crandom () ; 
 int random () ; 
 int trap_PointContents (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void BotRoamGoal(bot_state_t *bs, vec3_t goal) {
	int pc, i;
	float len, rnd;
	vec3_t dir, bestorg, belowbestorg;
	bsp_trace_t trace;

	for (i = 0; i < 10; i++) {
		//start at the bot origin
		VectorCopy(bs->origin, bestorg);
		rnd = random();
		if (rnd > 0.25) {
			//add a random value to the x-coordinate
			if (random() < 0.5) bestorg[0] -= 800 * random() + 100;
			else bestorg[0] += 800 * random() + 100;
		}
		if (rnd < 0.75) {
			//add a random value to the y-coordinate
			if (random() < 0.5) bestorg[1] -= 800 * random() + 100;
			else bestorg[1] += 800 * random() + 100;
		}
		//add a random value to the z-coordinate (NOTE: 48 = maxjump?)
		bestorg[2] += 2 * 48 * crandom();
		//trace a line from the origin to the roam target
		BotAI_Trace(&trace, bs->origin, NULL, NULL, bestorg, bs->entitynum, MASK_SOLID);
		//direction and length towards the roam target
		VectorSubtract(trace.endpos, bs->origin, dir);
		len = VectorNormalize(dir);
		//if the roam target is far away anough
		if (len > 200) {
			//the roam target is in the given direction before walls
			VectorScale(dir, len * trace.fraction - 40, dir);
			VectorAdd(bs->origin, dir, bestorg);
			//get the coordinates of the floor below the roam target
			belowbestorg[0] = bestorg[0];
			belowbestorg[1] = bestorg[1];
			belowbestorg[2] = bestorg[2] - 800;
			BotAI_Trace(&trace, bestorg, NULL, NULL, belowbestorg, bs->entitynum, MASK_SOLID);
			//
			if (!trace.startsolid) {
				trace.endpos[2]++;
				pc = trap_PointContents(trace.endpos, bs->entitynum);
				if (!(pc & (CONTENTS_LAVA | CONTENTS_SLIME))) {
					VectorCopy(bestorg, goal);
					return;
				}
			}
		}
	}
	VectorCopy(bestorg, goal);
}
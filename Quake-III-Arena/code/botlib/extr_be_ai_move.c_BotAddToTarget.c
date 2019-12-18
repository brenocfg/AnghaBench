#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int qtrue ; 

int BotAddToTarget(vec3_t start, vec3_t end, float maxdist, float *dist, vec3_t target)
{
	vec3_t dir;
	float curdist;

	VectorSubtract(end, start, dir);
	curdist = VectorNormalize(dir);
	if (*dist + curdist < maxdist)
	{
		VectorCopy(end, target);
		*dist += curdist;
		return qfalse;
	} //end if
	else
	{
		VectorMA(start, maxdist - *dist, dir, target);
		*dist = maxdist;
		return qtrue;
	} //end else
}
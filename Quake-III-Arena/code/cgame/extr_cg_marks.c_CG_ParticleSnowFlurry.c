#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qhandle_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_9__ {float alpha; int height; int width; int* vel; int* accel; int /*<<< orphan*/ * org; int /*<<< orphan*/  type; scalar_t__ pshader; scalar_t__ startfade; scalar_t__ endtime; int /*<<< orphan*/  end; int /*<<< orphan*/  start; scalar_t__ alphavel; scalar_t__ color; scalar_t__ time; struct TYPE_9__* next; } ;
typedef  TYPE_2__ cparticle_t ;
struct TYPE_8__ {int* angles; int /*<<< orphan*/  origin; scalar_t__ time2; scalar_t__ time; int /*<<< orphan*/ * origin2; } ;
struct TYPE_10__ {TYPE_1__ currentState; } ;
typedef  TYPE_3__ centity_t ;
struct TYPE_11__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Printf (char*) ; 
 int /*<<< orphan*/  P_WEATHER_FLURRY ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* active_particles ; 
 TYPE_5__ cg ; 
 int crandom () ; 
 TYPE_2__* free_particles ; 
 scalar_t__ qtrue ; 
 int rand () ; 

void CG_ParticleSnowFlurry (qhandle_t pshader, centity_t *cent)
{
	cparticle_t	*p;
	qboolean turb = qtrue;

	if (!pshader)
		CG_Printf ("CG_ParticleSnowFlurry pshader == ZERO!\n");

	if (!free_particles)
		return;
	p = free_particles;
	free_particles = p->next;
	p->next = active_particles;
	active_particles = p;
	p->time = cg.time;
	p->color = 0;
	p->alpha = 0.90f;
	p->alphavel = 0;

	p->start = cent->currentState.origin2[0];
	p->end = cent->currentState.origin2[1];
	
	p->endtime = cg.time + cent->currentState.time;
	p->startfade = cg.time + cent->currentState.time2;
	
	p->pshader = pshader;
	
	if (rand()%100 > 90)
	{
		p->height = 32;
		p->width = 32;
		p->alpha = 0.10f;
	}
	else
	{
		p->height = 1;
		p->width = 1;
	}

	p->vel[2] = -20;

	p->type = P_WEATHER_FLURRY;
	
	if (turb)
		p->vel[2] = -10;
	
	VectorCopy(cent->currentState.origin, p->org);

	p->org[0] = p->org[0];
	p->org[1] = p->org[1];
	p->org[2] = p->org[2];

	p->vel[0] = p->vel[1] = 0;
	
	p->accel[0] = p->accel[1] = p->accel[2] = 0;

	p->vel[0] += cent->currentState.angles[0] * 32 + (crandom() * 16);
	p->vel[1] += cent->currentState.angles[1] * 32 + (crandom() * 16);
	p->vel[2] += cent->currentState.angles[2];

	if (turb)
	{
		p->accel[0] = crandom () * 16;
		p->accel[1] = crandom () * 16;
	}

}
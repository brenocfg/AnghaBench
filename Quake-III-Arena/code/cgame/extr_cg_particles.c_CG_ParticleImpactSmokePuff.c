#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  scalar_t__ qhandle_t ;
struct TYPE_5__ {double alpha; int roll; int width; int height; int endheight; int endwidth; int /*<<< orphan*/  rotate; int /*<<< orphan*/  accel; int /*<<< orphan*/  vel; int /*<<< orphan*/  org; int /*<<< orphan*/  type; scalar_t__ endtime; scalar_t__ startfade; scalar_t__ pshader; scalar_t__ alphavel; scalar_t__ time; struct TYPE_5__* next; } ;
typedef  TYPE_1__ cparticle_t ;
struct TYPE_6__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Printf (char*) ; 
 int /*<<< orphan*/  P_SMOKE_IMPACT ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* active_particles ; 
 TYPE_3__ cg ; 
 int crandom () ; 
 TYPE_1__* free_particles ; 
 int /*<<< orphan*/  qtrue ; 
 int rand () ; 

void CG_ParticleImpactSmokePuff (qhandle_t pshader, vec3_t origin)
{
	cparticle_t	*p;

	if (!pshader)
		CG_Printf ("CG_ParticleImpactSmokePuff pshader == ZERO!\n");

	if (!free_particles)
		return;
	p = free_particles;
	free_particles = p->next;
	p->next = active_particles;
	active_particles = p;
	p->time = cg.time;
	p->alpha = 0.25;
	p->alphavel = 0;
	p->roll = crandom()*179;

	p->pshader = pshader;

	p->endtime = cg.time + 1000;
	p->startfade = cg.time + 100;

	p->width = rand()%4 + 8;
	p->height = rand()%4 + 8;

	p->endheight = p->height *2;
	p->endwidth = p->width * 2;

	p->endtime = cg.time + 500;

	p->type = P_SMOKE_IMPACT;

	VectorCopy( origin, p->org );
	VectorSet(p->vel, 0, 0, 20);
	VectorSet(p->accel, 0, 0, 20);

	p->rotate = qtrue;
}
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
struct TYPE_5__ {double alpha; int roll; int width; int height; int endheight; int endwidth; int* vel; int /*<<< orphan*/  color; int /*<<< orphan*/  rotate; int /*<<< orphan*/  accel; int /*<<< orphan*/  org; int /*<<< orphan*/  type; scalar_t__ startfade; scalar_t__ endtime; scalar_t__ pshader; scalar_t__ alphavel; scalar_t__ time; struct TYPE_5__* next; } ;
typedef  TYPE_1__ cparticle_t ;
struct TYPE_6__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOODRED ; 
 int /*<<< orphan*/  CG_Printf (char*) ; 
 int /*<<< orphan*/  P_SMOKE ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* active_particles ; 
 TYPE_3__ cg ; 
 TYPE_1__* free_particles ; 
 int /*<<< orphan*/  qfalse ; 
 int rand () ; 

void CG_Particle_Bleed (qhandle_t pshader, vec3_t start, vec3_t dir, int fleshEntityNum, int duration)
{
	cparticle_t	*p;

	if (!pshader)
		CG_Printf ("CG_Particle_Bleed pshader == ZERO!\n");

	if (!free_particles)
		return;
	p = free_particles;
	free_particles = p->next;
	p->next = active_particles;
	active_particles = p;
	p->time = cg.time;
	p->alpha = 1.0;
	p->alphavel = 0;
	p->roll = 0;

	p->pshader = pshader;

	p->endtime = cg.time + duration;
	
	if (fleshEntityNum)
		p->startfade = cg.time;
	else
		p->startfade = cg.time + 100;

	p->width = 4;
	p->height = 4;

	p->endheight = 4+rand()%3;
	p->endwidth = p->endheight;

	p->type = P_SMOKE;

	VectorCopy( start, p->org );
	p->vel[0] = 0;
	p->vel[1] = 0;
	p->vel[2] = -20;
	VectorClear( p->accel );

	p->rotate = qfalse;

	p->roll = rand()%179;
	
	p->color = BLOODRED;
	p->alpha = 0.75;

}
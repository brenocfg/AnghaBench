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
struct TYPE_9__ {double alpha; int height; int width; int endheight; int endwidth; int* vel; int roll; scalar_t__* accel; int /*<<< orphan*/  org; int /*<<< orphan*/  type; int /*<<< orphan*/  rotate; scalar_t__ pshader; int /*<<< orphan*/  end; int /*<<< orphan*/  start; scalar_t__ alphavel; scalar_t__ color; scalar_t__ startfade; scalar_t__ endtime; scalar_t__ time; struct TYPE_9__* next; } ;
typedef  TYPE_2__ cparticle_t ;
struct TYPE_8__ {int frame; int /*<<< orphan*/ * origin; int /*<<< orphan*/ * origin2; scalar_t__ time2; scalar_t__ time; } ;
struct TYPE_10__ {TYPE_1__ currentState; } ;
typedef  TYPE_3__ centity_t ;
struct TYPE_11__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Printf (char*) ; 
 int /*<<< orphan*/  P_SMOKE ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* active_particles ; 
 TYPE_5__ cg ; 
 int crandom () ; 
 TYPE_2__* free_particles ; 
 int /*<<< orphan*/  qfalse ; 

void CG_ParticleSmoke (qhandle_t pshader, centity_t *cent)
{

	// using cent->density = enttime
	//		 cent->frame = startfade
	cparticle_t	*p;

	if (!pshader)
		CG_Printf ("CG_ParticleSmoke == ZERO!\n");

	if (!free_particles)
		return;
	p = free_particles;
	free_particles = p->next;
	p->next = active_particles;
	active_particles = p;
	p->time = cg.time;
	
	p->endtime = cg.time + cent->currentState.time;
	p->startfade = cg.time + cent->currentState.time2;
	
	p->color = 0;
	p->alpha = 1.0;
	p->alphavel = 0;
	p->start = cent->currentState.origin[2];
	p->end = cent->currentState.origin2[2];
	p->pshader = pshader;
	p->rotate = qfalse;
	p->height = 8;
	p->width = 8;
	p->endheight = 32;
	p->endwidth = 32;
	p->type = P_SMOKE;
	
	VectorCopy(cent->currentState.origin, p->org);

	p->vel[0] = p->vel[1] = 0;
	p->accel[0] = p->accel[1] = p->accel[2] = 0;

	p->vel[2] = 5;

	if (cent->currentState.frame == 1)// reverse gravity	
		p->vel[2] *= -1;

	p->roll = 8 + (crandom() * 4);
}
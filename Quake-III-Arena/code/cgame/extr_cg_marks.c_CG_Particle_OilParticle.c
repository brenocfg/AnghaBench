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
struct TYPE_9__ {int time; double alpha; int roll; float endtime; float startfade; int width; int height; int endheight; int endwidth; int* vel; float snum; int* accel; int /*<<< orphan*/  rotate; int /*<<< orphan*/  org; int /*<<< orphan*/  type; scalar_t__ pshader; scalar_t__ alphavel; struct TYPE_9__* next; } ;
typedef  TYPE_2__ cparticle_t ;
struct TYPE_8__ {int time; int* origin2; int /*<<< orphan*/  origin; } ;
struct TYPE_10__ {TYPE_1__ currentState; } ;
typedef  TYPE_3__ centity_t ;
struct TYPE_11__ {int time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Printf (char*) ; 
 int /*<<< orphan*/  P_SMOKE ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* active_particles ; 
 TYPE_5__ cg ; 
 TYPE_2__* free_particles ; 
 int /*<<< orphan*/  qfalse ; 
 int rand () ; 

void CG_Particle_OilParticle (qhandle_t pshader, centity_t *cent)
{
	cparticle_t	*p;

	int			time;
	int			time2;
	float		ratio;

	float	duration = 1500;

	time = cg.time;
	time2 = cg.time + cent->currentState.time;

	ratio =(float)1 - ((float)time / (float)time2);

	if (!pshader)
		CG_Printf ("CG_Particle_OilParticle == ZERO!\n");

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
	
	p->startfade = p->endtime;

	p->width = 1;
	p->height = 3;

	p->endheight = 3;
	p->endwidth = 1;

	p->type = P_SMOKE;

	VectorCopy(cent->currentState.origin, p->org );	
	
	p->vel[0] = (cent->currentState.origin2[0] * (16 * ratio));
	p->vel[1] = (cent->currentState.origin2[1] * (16 * ratio));
	p->vel[2] = (cent->currentState.origin2[2]);

	p->snum = 1.0f;

	VectorClear( p->accel );

	p->accel[2] = -20;

	p->rotate = qfalse;

	p->roll = rand()%179;
	
	p->alpha = 0.75;

}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void** vec3_t ;
struct TYPE_8__ {float alpha; double height; double width; double endheight; double endwidth; float* org; int* vel; int* accel; int /*<<< orphan*/  type; int /*<<< orphan*/  pshader; scalar_t__ alphavel; int /*<<< orphan*/  color; scalar_t__ startfade; scalar_t__ endtime; scalar_t__ time; struct TYPE_8__* next; } ;
typedef  TYPE_2__ cparticle_t ;
struct TYPE_10__ {scalar_t__ time; } ;
struct TYPE_7__ {int /*<<< orphan*/  tracerShader; } ;
struct TYPE_9__ {TYPE_1__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMISIVEFADE ; 
 int /*<<< orphan*/  P_SMOKE ; 
 int /*<<< orphan*/  VectorCopy (void**,float*) ; 
 TYPE_2__* active_particles ; 
 TYPE_5__ cg ; 
 TYPE_4__ cgs ; 
 int crandom () ; 
 TYPE_2__* free_particles ; 

void CG_ParticleSparks (vec3_t org, vec3_t vel, int duration, float x, float y, float speed)
{
	cparticle_t	*p;

	if (!free_particles)
		return;
	p = free_particles;
	free_particles = p->next;
	p->next = active_particles;
	active_particles = p;
	p->time = cg.time;
	
	p->endtime = cg.time + duration;
	p->startfade = cg.time + duration/2;
	
	p->color = EMISIVEFADE;
	p->alpha = 0.4f;
	p->alphavel = 0;

	p->height = 0.5;
	p->width = 0.5;
	p->endheight = 0.5;
	p->endwidth = 0.5;

	p->pshader = cgs.media.tracerShader;

	p->type = P_SMOKE;
	
	VectorCopy(org, p->org);

	p->org[0] += (crandom() * x);
	p->org[1] += (crandom() * y);

	p->vel[0] = vel[0];
	p->vel[1] = vel[1];
	p->vel[2] = vel[2];

	p->accel[0] = p->accel[1] = p->accel[2] = 0;

	p->vel[0] += (crandom() * 4);
	p->vel[1] += (crandom() * 4);
	p->vel[2] += (20 + (crandom() * 10)) * speed;	

	p->accel[0] = crandom () * 4;
	p->accel[1] = crandom () * 4;
	
}
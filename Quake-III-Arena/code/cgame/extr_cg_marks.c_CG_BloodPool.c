#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_7__ {int /*<<< orphan*/  endpos; } ;
typedef  TYPE_1__ trace_t ;
typedef  scalar_t__ qhandle_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  localEntity_t ;
struct TYPE_8__ {double alpha; int roll; int width; int height; int endheight; int endwidth; int /*<<< orphan*/  color; int /*<<< orphan*/  rotate; int /*<<< orphan*/  accel; scalar_t__* vel; int /*<<< orphan*/  org; int /*<<< orphan*/  type; scalar_t__ pshader; scalar_t__ alphavel; scalar_t__ endtime; scalar_t__ startfade; scalar_t__ time; struct TYPE_8__* next; } ;
typedef  TYPE_2__ cparticle_t ;
struct TYPE_9__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOODRED ; 
 int /*<<< orphan*/  CG_Printf (char*) ; 
 int /*<<< orphan*/  P_FLAT_SCALEUP ; 
 int /*<<< orphan*/  ValidBloodPool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* active_particles ; 
 TYPE_4__ cg ; 
 TYPE_2__* free_particles ; 
 int /*<<< orphan*/  qfalse ; 
 int rand () ; 
 double random () ; 

void CG_BloodPool (localEntity_t *le, qhandle_t pshader, trace_t *tr)
{	
	cparticle_t	*p;
	qboolean	legit;
	vec3_t		start;
	float		rndSize;
	
	if (!pshader)
		CG_Printf ("CG_BloodPool pshader == ZERO!\n");

	if (!free_particles)
		return;
	
	VectorCopy (tr->endpos, start);
	legit = ValidBloodPool (start);

	if (!legit) 
		return;

	p = free_particles;
	free_particles = p->next;
	p->next = active_particles;
	active_particles = p;
	p->time = cg.time;
	
	p->endtime = cg.time + 3000;
	p->startfade = p->endtime;

	p->alpha = 1.0;
	p->alphavel = 0;
	p->roll = 0;

	p->pshader = pshader;

	rndSize = 0.4 + random()*0.6;

	p->width = 8*rndSize;
	p->height = 8*rndSize;

	p->endheight = 16*rndSize;
	p->endwidth = 16*rndSize;
	
	p->type = P_FLAT_SCALEUP;

	VectorCopy(start, p->org );
	
	p->vel[0] = 0;
	p->vel[1] = 0;
	p->vel[2] = 0;
	VectorClear( p->accel );

	p->rotate = qfalse;

	p->roll = rand()%179;
	
	p->alpha = 0.75;
	
	p->color = BLOODRED;
}
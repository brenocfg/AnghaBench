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
struct ide_timing {void* udma; void* cycle; void* recover; void* active; void* cyc8b; void* rec8b; void* act8b; void* setup; } ;

/* Variables and functions */
 unsigned int IDE_TIMING_ACT8B ; 
 unsigned int IDE_TIMING_ACTIVE ; 
 unsigned int IDE_TIMING_CYC8B ; 
 unsigned int IDE_TIMING_CYCLE ; 
 unsigned int IDE_TIMING_REC8B ; 
 unsigned int IDE_TIMING_RECOVER ; 
 unsigned int IDE_TIMING_SETUP ; 
 unsigned int IDE_TIMING_UDMA ; 
 void* max (void*,void*) ; 

void ide_timing_merge(struct ide_timing *a, struct ide_timing *b,
		      struct ide_timing *m, unsigned int what)
{
	if (what & IDE_TIMING_SETUP)
		m->setup   = max(a->setup,   b->setup);
	if (what & IDE_TIMING_ACT8B)
		m->act8b   = max(a->act8b,   b->act8b);
	if (what & IDE_TIMING_REC8B)
		m->rec8b   = max(a->rec8b,   b->rec8b);
	if (what & IDE_TIMING_CYC8B)
		m->cyc8b   = max(a->cyc8b,   b->cyc8b);
	if (what & IDE_TIMING_ACTIVE)
		m->active  = max(a->active,  b->active);
	if (what & IDE_TIMING_RECOVER)
		m->recover = max(a->recover, b->recover);
	if (what & IDE_TIMING_CYCLE)
		m->cycle   = max(a->cycle,   b->cycle);
	if (what & IDE_TIMING_UDMA)
		m->udma    = max(a->udma,    b->udma);
}
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
struct ata_timing {void* udma; void* cycle; void* dmack_hold; void* recover; void* active; void* cyc8b; void* rec8b; void* act8b; void* setup; } ;

/* Variables and functions */
 unsigned int ATA_TIMING_ACT8B ; 
 unsigned int ATA_TIMING_ACTIVE ; 
 unsigned int ATA_TIMING_CYC8B ; 
 unsigned int ATA_TIMING_CYCLE ; 
 unsigned int ATA_TIMING_DMACK_HOLD ; 
 unsigned int ATA_TIMING_REC8B ; 
 unsigned int ATA_TIMING_RECOVER ; 
 unsigned int ATA_TIMING_SETUP ; 
 unsigned int ATA_TIMING_UDMA ; 
 void* max (void*,void*) ; 

void ata_timing_merge(const struct ata_timing *a, const struct ata_timing *b,
		      struct ata_timing *m, unsigned int what)
{
	if (what & ATA_TIMING_SETUP  ) m->setup   = max(a->setup,   b->setup);
	if (what & ATA_TIMING_ACT8B  ) m->act8b   = max(a->act8b,   b->act8b);
	if (what & ATA_TIMING_REC8B  ) m->rec8b   = max(a->rec8b,   b->rec8b);
	if (what & ATA_TIMING_CYC8B  ) m->cyc8b   = max(a->cyc8b,   b->cyc8b);
	if (what & ATA_TIMING_ACTIVE ) m->active  = max(a->active,  b->active);
	if (what & ATA_TIMING_RECOVER) m->recover = max(a->recover, b->recover);
	if (what & ATA_TIMING_DMACK_HOLD) m->dmack_hold = max(a->dmack_hold, b->dmack_hold);
	if (what & ATA_TIMING_CYCLE  ) m->cycle   = max(a->cycle,   b->cycle);
	if (what & ATA_TIMING_UDMA   ) m->udma    = max(a->udma,    b->udma);
}
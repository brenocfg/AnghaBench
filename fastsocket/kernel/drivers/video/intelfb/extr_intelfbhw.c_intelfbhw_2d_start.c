#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int physical; int size; } ;
struct intelfb_info {int ring_active; TYPE_1__ ring; int /*<<< orphan*/  accel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*,int /*<<< orphan*/ ,int) ; 
 int GTT_PAGE_SIZE ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PRI_RING_HEAD ; 
 int /*<<< orphan*/  PRI_RING_LENGTH ; 
 int /*<<< orphan*/  PRI_RING_START ; 
 int /*<<< orphan*/  PRI_RING_TAIL ; 
 int RING_ENABLE ; 
 int RING_LENGTH_MASK ; 
 int RING_NO_REPORT ; 
 int RING_START_MASK ; 
 int /*<<< orphan*/  refresh_ring (struct intelfb_info*) ; 

void intelfbhw_2d_start(struct intelfb_info *dinfo)
{
#if VERBOSE > 0
	DBG_MSG("intelfbhw_2d_start: accel: %d, ring_active: %d\n",
		dinfo->accel, dinfo->ring_active);
#endif

	if (!dinfo->accel)
		return;

	/* Initialise the primary ring buffer. */
	OUTREG(PRI_RING_LENGTH, 0);
	OUTREG(PRI_RING_TAIL, 0);
	OUTREG(PRI_RING_HEAD, 0);

	OUTREG(PRI_RING_START, dinfo->ring.physical & RING_START_MASK);
	OUTREG(PRI_RING_LENGTH,
		((dinfo->ring.size - GTT_PAGE_SIZE) & RING_LENGTH_MASK) |
		RING_NO_REPORT | RING_ENABLE);
	refresh_ring(dinfo);
	dinfo->ring_active = 1;
}
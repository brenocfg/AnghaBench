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
typedef  int u32 ;
struct intelfb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*) ; 
 int /*<<< orphan*/  DO_RING_IDLE () ; 
 scalar_t__ FENCE ; 
 int FENCE_NUM ; 
 int INREG (scalar_t__) ; 
 int /*<<< orphan*/  OUTREG (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PRI_RING_HEAD ; 
 scalar_t__ PRI_RING_LENGTH ; 
 scalar_t__ PRI_RING_START ; 
 scalar_t__ PRI_RING_TAIL ; 
 int RING_ENABLE ; 
 int /*<<< orphan*/  intelfbhw_do_sync (struct intelfb_info*) ; 
 int /*<<< orphan*/  refresh_ring (struct intelfb_info*) ; 

__attribute__((used)) static void reset_state(struct intelfb_info *dinfo)
{
	int i;
	u32 tmp;

#if VERBOSE > 0
	DBG_MSG("reset_state\n");
#endif

	for (i = 0; i < FENCE_NUM; i++)
		OUTREG(FENCE + (i << 2), 0);

	/* Flush the ring buffer if it's enabled. */
	tmp = INREG(PRI_RING_LENGTH);
	if (tmp & RING_ENABLE) {
#if VERBOSE > 0
		DBG_MSG("reset_state: ring was enabled\n");
#endif
		refresh_ring(dinfo);
		intelfbhw_do_sync(dinfo);
		DO_RING_IDLE();
	}

	OUTREG(PRI_RING_LENGTH, 0);
	OUTREG(PRI_RING_HEAD, 0);
	OUTREG(PRI_RING_TAIL, 0);
	OUTREG(PRI_RING_START, 0);
}
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
struct bc_state {int /*<<< orphan*/  cs; int /*<<< orphan*/  at_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  EV_BC_OPEN ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gigaset_add_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gigaset_schedule_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gigaset_bchannel_up(struct bc_state *bcs)
{
	gigaset_add_event(bcs->cs, &bcs->at_state, EV_BC_OPEN, NULL, 0, NULL);

	gig_dbg(DEBUG_CMD, "scheduling BC_OPEN");
	gigaset_schedule_event(bcs->cs);
}
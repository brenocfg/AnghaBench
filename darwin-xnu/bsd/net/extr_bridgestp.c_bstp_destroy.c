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
struct bstp_port {scalar_t__ bp_active; int /*<<< orphan*/  bp_rtagetask; int /*<<< orphan*/  bp_statetask; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bstp_task_drain (int /*<<< orphan*/ *) ; 

void
bstp_destroy(struct bstp_port *bp)
{
	KASSERT(bp->bp_active == 0, ("port is still attached"));
	bstp_task_drain(&bp->bp_statetask);
	bstp_task_drain(&bp->bp_rtagetask);
}
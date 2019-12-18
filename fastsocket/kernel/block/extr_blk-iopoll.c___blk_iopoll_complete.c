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
struct blk_iopoll {int /*<<< orphan*/  state; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOPOLL_F_SCHED ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 

void __blk_iopoll_complete(struct blk_iopoll *iop)
{
	list_del(&iop->list);
	smp_mb__before_clear_bit();
	clear_bit_unlock(IOPOLL_F_SCHED, &iop->state);
}
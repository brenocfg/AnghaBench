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
struct blk_iopoll {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOPOLL_F_DISABLE ; 
 int /*<<< orphan*/  IOPOLL_F_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void blk_iopoll_disable(struct blk_iopoll *iop)
{
	set_bit(IOPOLL_F_DISABLE, &iop->state);
	while (test_and_set_bit(IOPOLL_F_SCHED, &iop->state))
		msleep(1);
	clear_bit(IOPOLL_F_DISABLE, &iop->state);
}
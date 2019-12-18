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
struct blk_iopoll {int weight; int /*<<< orphan*/  state; int /*<<< orphan*/ * poll; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  blk_iopoll_fn ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOPOLL_F_SCHED ; 
 int /*<<< orphan*/  memset (struct blk_iopoll*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void blk_iopoll_init(struct blk_iopoll *iop, int weight, blk_iopoll_fn *poll_fn)
{
	memset(iop, 0, sizeof(*iop));
	INIT_LIST_HEAD(&iop->list);
	iop->weight = weight;
	iop->poll = poll_fn;
	set_bit(IOPOLL_F_SCHED, &iop->state);
}
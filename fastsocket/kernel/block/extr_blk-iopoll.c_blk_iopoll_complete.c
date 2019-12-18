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
struct blk_iopoll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_iopoll_complete (struct blk_iopoll*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void blk_iopoll_complete(struct blk_iopoll *iopoll)
{
	unsigned long flags;

	local_irq_save(flags);
	__blk_iopoll_complete(iopoll);
	local_irq_restore(flags);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mv_xor_chan {int /*<<< orphan*/  idx; TYPE_2__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_dump_xor_regs (struct mv_xor_chan*) ; 

__attribute__((used)) static void mv_xor_err_interrupt_handler(struct mv_xor_chan *chan,
					 u32 intr_cause)
{
	if (intr_cause & (1 << 4)) {
	     dev_dbg(chan->device->common.dev,
		     "ignore this error\n");
	     return;
	}

	dev_printk(KERN_ERR, chan->device->common.dev,
		   "error on chan %d. intr cause 0x%08x.\n",
		   chan->idx, intr_cause);

	mv_dump_xor_regs(chan);
	BUG();
}
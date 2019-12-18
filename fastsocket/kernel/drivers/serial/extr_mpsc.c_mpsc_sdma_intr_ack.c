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
struct TYPE_4__ {scalar_t__ line; } ;
struct mpsc_port_info {TYPE_2__ port; TYPE_1__* shared_regs; scalar_t__ mirror_regs; } ;
struct TYPE_3__ {scalar_t__ sdma_intr_base; scalar_t__ SDMA_INTR_CAUSE_m; } ;

/* Variables and functions */
 scalar_t__ SDMA_INTR_CAUSE ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void mpsc_sdma_intr_ack(struct mpsc_port_info *pi)
{
	pr_debug("mpsc_sdma_intr_ack[%d]: Acknowledging IRQ\n", pi->port.line);

	if (pi->mirror_regs)
		pi->shared_regs->SDMA_INTR_CAUSE_m = 0;
	writeb(0x00, pi->shared_regs->sdma_intr_base + SDMA_INTR_CAUSE
			+ pi->port.line);
}
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
struct vio_port {int /*<<< orphan*/  crq_work; int /*<<< orphan*/  dma_dev; } ;
struct srp_target {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vio_port* target_to_port (struct srp_target*) ; 
 int /*<<< orphan*/  vio_disable_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtgtd ; 

__attribute__((used)) static irqreturn_t ibmvstgt_interrupt(int dummy, void *data)
{
	struct srp_target *target = data;
	struct vio_port *vport = target_to_port(target);

	vio_disable_interrupts(vport->dma_dev);
	queue_work(vtgtd, &vport->crq_work);

	return IRQ_HANDLED;
}
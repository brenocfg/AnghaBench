#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtip_port {int /*<<< orphan*/  cmd_slot; int /*<<< orphan*/  cmd_slot_unal; struct mtip_cmd* commands; TYPE_2__* dd; } ;
struct mtip_cmd {int unaligned; int /*<<< orphan*/  active; int /*<<< orphan*/  direction; int /*<<< orphan*/  scatter_ents; int /*<<< orphan*/  sg; int /*<<< orphan*/ * comp_func; int /*<<< orphan*/  (* async_callback ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  async_data; } ;
struct driver_data {TYPE_3__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int PORT_IRQ_TF_ERR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int)) ; 
 int /*<<< orphan*/  release_slot (struct mtip_port*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtip_async_complete(struct mtip_port *port,
				int tag,
				void *data,
				int status)
{
	struct mtip_cmd *command;
	struct driver_data *dd = data;
	int cb_status = status ? -EIO : 0;

	if (unlikely(!dd) || unlikely(!port))
		return;

	command = &port->commands[tag];

	if (unlikely(status == PORT_IRQ_TF_ERR)) {
		dev_warn(&port->dd->pdev->dev,
			"Command tag %d failed due to TFE\n", tag);
	}

	/* Upper layer callback */
	if (likely(command->async_callback))
		command->async_callback(command->async_data, cb_status);

	command->async_callback = NULL;
	command->comp_func = NULL;

	/* Unmap the DMA scatter list entries */
	dma_unmap_sg(&dd->pdev->dev,
		command->sg,
		command->scatter_ents,
		command->direction);

	/* Clear the allocated and active bits for the command */
	atomic_set(&port->commands[tag].active, 0);
	release_slot(port, tag);

	if (unlikely(command->unaligned))
		up(&port->cmd_slot_unal);
	else
		up(&port->cmd_slot);
}
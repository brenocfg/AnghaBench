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
struct mtip_port {int* allocated; int /*<<< orphan*/  cmd_slot; TYPE_2__* dd; struct mtip_cmd* commands; } ;
struct mtip_cmd {int /*<<< orphan*/  direction; int /*<<< orphan*/  scatter_ents; int /*<<< orphan*/  sg; int /*<<< orphan*/ * async_data; int /*<<< orphan*/  (* async_callback ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  active; } ;
struct driver_data {int /*<<< orphan*/  dd_flag; struct mtip_port* port; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  MTIP_DDF_CLEANUP_BIT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtip_command_cleanup(struct driver_data *dd)
{
	int group = 0, commandslot = 0, commandindex = 0;
	struct mtip_cmd *command;
	struct mtip_port *port = dd->port;
	static int in_progress;

	if (in_progress)
		return;

	in_progress = 1;

	for (group = 0; group < 4; group++) {
		for (commandslot = 0; commandslot < 32; commandslot++) {
			if (!(port->allocated[group] & (1 << commandslot)))
				continue;

			commandindex = group << 5 | commandslot;
			command = &port->commands[commandindex];

			if (atomic_read(&command->active)
			    && (command->async_callback)) {
				command->async_callback(command->async_data,
					-ENODEV);
				command->async_callback = NULL;
				command->async_data = NULL;
			}

			dma_unmap_sg(&port->dd->pdev->dev,
				command->sg,
				command->scatter_ents,
				command->direction);
		}
	}

	up(&port->cmd_slot);

	set_bit(MTIP_DDF_CLEANUP_BIT, &dd->dd_flag);
	in_progress = 0;
}
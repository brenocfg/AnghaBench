#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtip_port {unsigned long flags; long ic_pause_timer; int /*<<< orphan*/  cmd_timer; int /*<<< orphan*/  svc_wait; TYPE_2__* dd; int /*<<< orphan*/  cmd_slot; struct mtip_cmd* commands; int /*<<< orphan*/ * completed; } ;
struct mtip_cmd {unsigned long comp_time; int /*<<< orphan*/  active; int /*<<< orphan*/  direction; int /*<<< orphan*/  scatter_ents; int /*<<< orphan*/  sg; int /*<<< orphan*/ * comp_func; int /*<<< orphan*/  (* async_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  async_data; scalar_t__ command; } ;
struct host_to_dev_fis {int dummy; } ;
struct TYPE_5__ {unsigned long dd_flag; int slot_groups; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int MTIP_DDF_RESUME_BIT ; 
 int MTIP_PF_DM_ACTIVE_BIT ; 
 int MTIP_PF_EH_ACTIVE_BIT ; 
 int MTIP_PF_IC_ACTIVE_BIT ; 
 int MTIP_PF_SE_ACTIVE_BIT ; 
 int MTIP_TAG_INTERNAL ; 
 int MTIP_TIMEOUT_CHECK_PERIOD ; 
 int SLOTBITS_IN_LONGS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mtip_device_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  print_tags (TYPE_2__*,char*,unsigned long*,int) ; 
 int /*<<< orphan*/  release_slot (struct mtip_port*,int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 scalar_t__ time_after (scalar_t__,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtip_timeout_function(unsigned long int data)
{
	struct mtip_port *port = (struct mtip_port *) data;
	struct host_to_dev_fis *fis;
	struct mtip_cmd *command;
	int tag, cmdto_cnt = 0;
	unsigned int bit, group;
	unsigned int num_command_slots;
	unsigned long to, tagaccum[SLOTBITS_IN_LONGS];

	if (unlikely(!port))
		return;

	if (test_bit(MTIP_DDF_RESUME_BIT, &port->dd->dd_flag)) {
		mod_timer(&port->cmd_timer,
			jiffies + msecs_to_jiffies(30000));
		return;
	}
	/* clear the tag accumulator */
	memset(tagaccum, 0, SLOTBITS_IN_LONGS * sizeof(long));
	num_command_slots = port->dd->slot_groups * 32;

	for (tag = 0; tag < num_command_slots; tag++) {
		/*
		 * Skip internal command slot as it has
		 * its own timeout mechanism
		 */
		if (tag == MTIP_TAG_INTERNAL)
			continue;

		if (atomic_read(&port->commands[tag].active) &&
		   (time_after(jiffies, port->commands[tag].comp_time))) {
			group = tag >> 5;
			bit = tag & 0x1F;

			command = &port->commands[tag];
			fis = (struct host_to_dev_fis *) command->command;

			set_bit(tag, tagaccum);
			cmdto_cnt++;
			if (cmdto_cnt == 1)
				set_bit(MTIP_PF_EH_ACTIVE_BIT, &port->flags);

			/*
			 * Clear the completed bit. This should prevent
			 *  any interrupt handlers from trying to retire
			 *  the command.
			 */
			writel(1 << bit, port->completed[group]);

			/* Call the async completion callback. */
			if (likely(command->async_callback))
				command->async_callback(command->async_data,
							 -EIO);
			command->async_callback = NULL;
			command->comp_func = NULL;

			/* Unmap the DMA scatter list entries */
			dma_unmap_sg(&port->dd->pdev->dev,
					command->sg,
					command->scatter_ents,
					command->direction);

			/*
			 * Clear the allocated bit and active tag for the
			 * command.
			 */
			atomic_set(&port->commands[tag].active, 0);
			release_slot(port, tag);

			up(&port->cmd_slot);
		}
	}

	if (cmdto_cnt) {
		print_tags(port->dd, "timed out", tagaccum, cmdto_cnt);
		if (!test_bit(MTIP_PF_IC_ACTIVE_BIT, &port->flags)) {
			mtip_device_reset(port->dd);
			wake_up_interruptible(&port->svc_wait);
		}
		clear_bit(MTIP_PF_EH_ACTIVE_BIT, &port->flags);
	}

	if (port->ic_pause_timer) {
		to  = port->ic_pause_timer + msecs_to_jiffies(1000);
		if (time_after(jiffies, to)) {
			if (!test_bit(MTIP_PF_IC_ACTIVE_BIT, &port->flags)) {
				port->ic_pause_timer = 0;
				clear_bit(MTIP_PF_SE_ACTIVE_BIT, &port->flags);
				clear_bit(MTIP_PF_DM_ACTIVE_BIT, &port->flags);
				clear_bit(MTIP_PF_IC_ACTIVE_BIT, &port->flags);
				wake_up_interruptible(&port->svc_wait);
			}


		}
	}

	/* Restart the timer */
	mod_timer(&port->cmd_timer,
		jiffies + msecs_to_jiffies(MTIP_TIMEOUT_CHECK_PERIOD));
}
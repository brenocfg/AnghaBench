#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mtip_port {struct mtip_cmd* commands; int /*<<< orphan*/ * completed; } ;
struct mtip_cmd {int /*<<< orphan*/  comp_data; int /*<<< orphan*/  (* comp_func ) (struct mtip_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct driver_data {int slot_groups; TYPE_1__* pdev; struct mtip_port* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MTIP_TAG_INTERNAL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ likely (int /*<<< orphan*/  (*) (struct mtip_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 scalar_t__ mtip_check_surprise_removal (TYPE_1__*) ; 
 int /*<<< orphan*/  mtip_command_cleanup (struct driver_data*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtip_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mtip_process_sdbf(struct driver_data *dd)
{
	struct mtip_port  *port = dd->port;
	int group, tag, bit;
	u32 completed;
	struct mtip_cmd *command;

	/* walk all bits in all slot groups */
	for (group = 0; group < dd->slot_groups; group++) {
		completed = readl(port->completed[group]);
		if (!completed)
			continue;

		/* clear completed status register in the hardware.*/
		writel(completed, port->completed[group]);

		/* Process completed commands. */
		for (bit = 0;
		     (bit < 32) && completed;
		     bit++, completed >>= 1) {
			if (completed & 0x01) {
				tag = (group << 5) | bit;

				/* skip internal command slot. */
				if (unlikely(tag == MTIP_TAG_INTERNAL))
					continue;

				command = &port->commands[tag];
				/* make internal callback */
				if (likely(command->comp_func)) {
					command->comp_func(
						port,
						tag,
						command->comp_data,
						0);
				} else {
					dev_warn(&dd->pdev->dev,
						"Null completion "
						"for tag %d",
						tag);

					if (mtip_check_surprise_removal(
						dd->pdev)) {
						mtip_command_cleanup(dd);
						return;
					}
				}
			}
		}
	}
}
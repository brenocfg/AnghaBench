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
struct mtip_port {TYPE_1__* dd; int /*<<< orphan*/  allocated; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int slot_groups; TYPE_2__* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ mtip_check_surprise_removal (TYPE_2__*) ; 
 int /*<<< orphan*/  mtip_command_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_slot(struct mtip_port *port)
{
	int slot, i;
	unsigned int num_command_slots = port->dd->slot_groups * 32;

	/*
	 * Try 10 times, because there is a small race here.
	 *  that's ok, because it's still cheaper than a lock.
	 *
	 * Race: Since this section is not protected by lock, same bit
	 * could be chosen by different process contexts running in
	 * different processor. So instead of costly lock, we are going
	 * with loop.
	 */
	for (i = 0; i < 10; i++) {
		slot = find_next_zero_bit(port->allocated,
					 num_command_slots, 1);
		if ((slot < num_command_slots) &&
		    (!test_and_set_bit(slot, port->allocated)))
			return slot;
	}
	dev_warn(&port->dd->pdev->dev, "Failed to get a tag.\n");

	if (mtip_check_surprise_removal(port->dd->pdev)) {
		/* Device not present, clean outstanding commands */
		mtip_command_cleanup(port->dd);
	}
	return -1;
}
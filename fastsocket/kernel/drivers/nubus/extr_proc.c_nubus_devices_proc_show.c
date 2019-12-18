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
struct seq_file {int dummy; } ;
struct nubus_dev {struct nubus_dev* next; TYPE_1__* board; int /*<<< orphan*/  dr_hw; int /*<<< orphan*/  dr_sw; int /*<<< orphan*/  type; int /*<<< orphan*/  category; } ;
struct TYPE_2__ {int /*<<< orphan*/  slot_addr; int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 struct nubus_dev* nubus_devices ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
nubus_devices_proc_show(struct seq_file *m, void *v)
{
	struct nubus_dev *dev = nubus_devices;

	while (dev) {
		seq_printf(m, "%x\t%04x %04x %04x %04x",
			      dev->board->slot,
			      dev->category,
			      dev->type,
			      dev->dr_sw,
			      dev->dr_hw);
		seq_printf(m, "\t%08lx\n", dev->board->slot_addr);
		dev = dev->next;
	}
	return 0;
}
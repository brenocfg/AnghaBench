#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mite_struct {TYPE_2__* pcidev; scalar_t__ used; struct mite_struct* next; } ;
struct comedi_device {TYPE_4__* board_ptr; } ;
struct TYPE_8__ {scalar_t__ dev_id; } ;
struct TYPE_7__ {struct mite_struct* mite; } ;
struct TYPE_6__ {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_5__ {int number; } ;

/* Variables and functions */
 int EIO ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ mite_device_id (struct mite_struct*) ; 
 struct mite_struct* mite_devices ; 
 int /*<<< orphan*/  mite_list_devices () ; 
 int n_ni_65xx_boards ; 
 TYPE_4__* ni_65xx_boards ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_3__* private (struct comedi_device*) ; 

__attribute__((used)) static int ni_65xx_find_device(struct comedi_device *dev, int bus, int slot)
{
	struct mite_struct *mite;
	int i;

	for (mite = mite_devices; mite; mite = mite->next) {
		if (mite->used)
			continue;
		if (bus || slot) {
			if (bus != mite->pcidev->bus->number ||
			    slot != PCI_SLOT(mite->pcidev->devfn))
				continue;
		}
		for (i = 0; i < n_ni_65xx_boards; i++) {
			if (mite_device_id(mite) == ni_65xx_boards[i].dev_id) {
				dev->board_ptr = ni_65xx_boards + i;
				private(dev)->mite = mite;
				return 0;
			}
		}
	}
	printk("no device found\n");
	mite_list_devices();
	return -EIO;
}
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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ pci_dev_p; scalar_t__ plx_regbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_PDEBUG (char*) ; 
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 TYPE_1__* info ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 
 int /*<<< orphan*/  reset_board (struct comedi_device*) ; 

__attribute__((used)) static int me4000_detach(struct comedi_device *dev)
{
	CALL_PDEBUG("In me4000_detach()\n");

	if (info) {
		if (info->pci_dev_p) {
			reset_board(dev);
			if (info->plx_regbase)
				comedi_pci_disable(info->pci_dev_p);
			pci_dev_put(info->pci_dev_p);
		}
	}

	return 0;
}
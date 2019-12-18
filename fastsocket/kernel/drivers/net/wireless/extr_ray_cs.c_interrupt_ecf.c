#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ amem; scalar_t__ sram; struct pcmcia_device* finder; } ;
typedef  TYPE_1__ ray_dev_t ;

/* Variables and functions */
 scalar_t__ CIS_OFFSET ; 
 int /*<<< orphan*/  DEBUG (int,char*,...) ; 
 scalar_t__ ECF_INTR_OFFSET ; 
 int ECF_INTR_SET ; 
 scalar_t__ SCB_BASE ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int interrupt_ecf(ray_dev_t *local, int ccs)
{
	int i = 50;
	struct pcmcia_device *link = local->finder;

	if (!(pcmcia_dev_present(link))) {
		DEBUG(2, "ray_cs interrupt_ecf - device not present\n");
		return -1;
	}
	DEBUG(2, "interrupt_ecf(local=%p, ccs = 0x%x\n", local, ccs);

	while (i &&
	       (readb(local->amem + CIS_OFFSET + ECF_INTR_OFFSET) &
		ECF_INTR_SET))
		i--;
	if (i == 0) {
		DEBUG(2, "ray_cs interrupt_ecf card not ready for interrupt\n");
		return -1;
	}
	/* Fill the mailbox, then kick the card */
	writeb(ccs, local->sram + SCB_BASE);
	writeb(ECF_INTR_SET, local->amem + CIS_OFFSET + ECF_INTR_OFFSET);
	return 0;
}
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
struct TYPE_6__ {int imask; } ;
struct TYPE_4__ {int /*<<< orphan*/  control; } ;
struct TYPE_5__ {TYPE_1__ pci; } ;

/* Variables and functions */
 unsigned int CRIME_IRQ_BASE ; 
 int /*<<< orphan*/  MACEPCI_CONTROL_INT (scalar_t__) ; 
 scalar_t__ MACEPCI_SCSI0_IRQ ; 
 TYPE_3__* crime ; 
 int crime_mask ; 
 TYPE_2__* mace ; 
 int /*<<< orphan*/  macepci_mask ; 

__attribute__((used)) static void enable_macepci_irq(unsigned int irq)
{
	macepci_mask |= MACEPCI_CONTROL_INT(irq - MACEPCI_SCSI0_IRQ);
	mace->pci.control = macepci_mask;
	crime_mask |= 1 << (irq - CRIME_IRQ_BASE);
	crime->imask = crime_mask;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  DAC960_Controller_T ;

/* Variables and functions */
 int /*<<< orphan*/ ** DAC960_Controllers ; 
 int /*<<< orphan*/  DAC960_FinalizeController (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void DAC960_Remove(struct pci_dev *PCI_Device)
{
  int Controller_Number = (long)pci_get_drvdata(PCI_Device);
  DAC960_Controller_T *Controller = DAC960_Controllers[Controller_Number];
  if (Controller != NULL)
      DAC960_FinalizeController(Controller);
}
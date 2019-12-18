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

/* Variables and functions */
 scalar_t__ Configuration1 ; 
 int /*<<< orphan*/  PCI_bus ; 
 scalar_t__* addresses ; 
 scalar_t__ bios_base ; 
 scalar_t__ chip ; 
 int inb (scalar_t__) ; 
 int* ints ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 scalar_t__ tmc18c30 ; 

__attribute__((used)) static int fdomain_get_irq( int base )
{
   int options = inb(base + Configuration1);

#if DEBUG_DETECT
   printk("scsi: <fdomain> Options = %x\n", options);
#endif
 
   /* Check for board with lowest bios_base --
      this isn't valid for the 18c30 or for
      boards on the PCI bus, so just assume we
      have the right board. */

   if (chip != tmc18c30 && !PCI_bus && addresses[(options & 0xc0) >> 6 ] != bios_base)
   	return 0;
   return ints[(options & 0x0e) >> 1];
}
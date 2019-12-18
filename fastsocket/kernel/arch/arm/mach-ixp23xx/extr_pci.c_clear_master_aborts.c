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
typedef  int u32 ;

/* Variables and functions */
 int volatile* IXP23XX_PCI_CMDSTAT ; 
 int volatile* IXP23XX_PCI_CONTROL ; 

int clear_master_aborts(void)
{
	volatile u32 temp;

	temp = *IXP23XX_PCI_CONTROL;

	/*
	 * master abort and cmd tgt err
	 */
	if (temp & ((1 << 8) | (1 << 5)))
		*IXP23XX_PCI_CONTROL = temp;

	temp = *IXP23XX_PCI_CMDSTAT;

	if (temp & (1 << 29))
		*IXP23XX_PCI_CMDSTAT = temp;

	return 0;
}
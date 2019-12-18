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
struct iga_par {int dummy; } ;

/* Variables and functions */
 int IGA_ATTR_CTL ; 
 int /*<<< orphan*/  IGA_EXT_CNTRL ; 
 scalar_t__ IGA_IDX_OVERSCAN_COLOR ; 
 int IGA_IDX_VGA_OVERSCAN ; 
 int /*<<< orphan*/  iga_outb (struct iga_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_inb (struct iga_par*,int) ; 
 int /*<<< orphan*/  pci_outb (struct iga_par*,int,int) ; 

__attribute__((used)) static void iga_blank_border(struct iga_par *par)
{
        int i;
#if 0
	/*
	 * PROM does this for us, so keep this code as a reminder
	 * about required read from 0x3DA and writing of 0x20 in the end.
	 */
	(void) pci_inb(par, 0x3DA);		/* required for every access */
	pci_outb(par, IGA_IDX_VGA_OVERSCAN, IGA_ATTR_CTL);
	(void) pci_inb(par, IGA_ATTR_CTL+1);
	pci_outb(par, 0x38, IGA_ATTR_CTL);
	pci_outb(par, 0x20, IGA_ATTR_CTL);	/* re-enable visual */
#endif
	/*
	 * This does not work as it was designed because the overscan
	 * color is looked up in the palette. Therefore, under X11
	 * overscan changes color.
	 */
	for (i=0; i < 3; i++)
		iga_outb(par, 0, IGA_EXT_CNTRL, IGA_IDX_OVERSCAN_COLOR + i);
}
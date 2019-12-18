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
typedef  int u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 unsigned int VIA_BAD_PREQ ; 
 unsigned int VIA_SET_FIFO ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void via_config_fifo(struct pci_dev *pdev, unsigned int flags)
{
	u8 enable;

	/* 0x40 low bits indicate enabled channels */
	pci_read_config_byte(pdev, 0x40 , &enable);
	enable &= 3;

	if (flags & VIA_SET_FIFO) {
		static const u8 fifo_setting[4] = {0x00, 0x60, 0x00, 0x20};
		u8 fifo;

		pci_read_config_byte(pdev, 0x43, &fifo);

		/* Clear PREQ# until DDACK# for errata */
		if (flags & VIA_BAD_PREQ)
			fifo &= 0x7F;
		else
			fifo &= 0x9f;
		/* Turn on FIFO for enabled channels */
		fifo |= fifo_setting[enable];
		pci_write_config_byte(pdev, 0x43, fifo);
	}
}
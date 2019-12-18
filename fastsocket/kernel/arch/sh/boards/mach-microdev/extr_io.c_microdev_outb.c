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
 unsigned long IO_LAN91C111_BASE ; 
 unsigned long IO_LAN91C111_EXTENT ; 
 unsigned long PCIBIOS_MIN_IO ; 
 scalar_t__ PORT2ADDR (unsigned long) ; 
 unsigned short microdev_inw (unsigned long const) ; 
 int /*<<< orphan*/  microdev_outw (unsigned short,unsigned long const) ; 
 int /*<<< orphan*/  microdev_pci_outb (unsigned char,unsigned long) ; 

void microdev_outb(unsigned char b, unsigned long port)
{
#ifdef CONFIG_PCI
	if (port >= PCIBIOS_MIN_IO) {
		microdev_pci_outb(b, port);
		return;
	}
#endif

	/*
	 *	There is a board feature with the current SH4-202 MicroDev in
	 *	that the 2 byte enables (nBE0 and nBE1) are tied together (and
	 *	to the Chip Select Line (Ethernet_CS)). Due to this connectivity,
	 *	it is not possible to safely perform 8-bit writes to the
	 *	Ethernet registers, as 16-bits will be consumed from the Data
	 *	lines (corrupting the other byte).  Hence, this function is
	 *	written to implement 16-bit read/modify/write for all byte-wide
	 *	accesses.
	 *
	 *	Note: there is no problem with byte READS (even or odd).
	 *
	 *			Sean McGoogan - 16th June 2003.
	 */
	if ((port >= IO_LAN91C111_BASE) &&
	    (port <  IO_LAN91C111_BASE + IO_LAN91C111_EXTENT)) {
			/*
			 * Then are trying to perform a byte-write to the
			 * LAN91C111.  This needs special care.
			 */
		if (port % 2 == 1) {	/* is the port odd ? */
			/* unset bit-0, i.e. make even */
			const unsigned long evenPort = port-1;
			unsigned short word;

			/*
			 * do a 16-bit read/write to write to 'port',
			 * preserving even byte.
			 *
			 *	Even addresses are bits 0-7
			 *	Odd  addresses are bits 8-15
			 */
			word = microdev_inw(evenPort);
			word = (word & 0xffu) | (b << 8);
			microdev_outw(word, evenPort);
		} else {
			/* else, we are trying to do an even byte write */
			unsigned short word;

			/*
			 * do a 16-bit read/write to write to 'port',
			 * preserving odd byte.
			 *
			 *	Even addresses are bits 0-7
			 *	Odd  addresses are bits 8-15
			 */
			word = microdev_inw(port);
			word = (word & 0xff00u) | (b);
			microdev_outw(word, port);
		}
	} else {
		*(volatile unsigned char*)PORT2ADDR(port) = b;
	}
}
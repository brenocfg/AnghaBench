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
struct hfc_multi {scalar_t__ pci_iobase; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

inline void
writepcibridge(struct hfc_multi *hc, unsigned char address, unsigned char data)
{
	unsigned short cipv;
	unsigned int datav;

	if (!hc->pci_iobase)
		return;

	if (address == 0)
		cipv = 0x4000;
	else
		cipv = 0x5800;

	/* select local bridge port address by writing to CIP port */
	outw(cipv, hc->pci_iobase + 4);
	/* define a 32 bit dword with 4 identical bytes for write sequence */
	datav = data | ((__u32) data << 8) | ((__u32) data << 16) |
	    ((__u32) data << 24);

	/*
	 * write this 32 bit dword to the bridge data port
	 * this will initiate a write sequence of up to 4 writes to the same
	 * address on the local bus interface the number of write accesses
	 * is undefined but >=1 and depends on the next PCI transaction
	 * during write sequence on the local bus
	 */
	outl(datav, hc->pci_iobase);
}
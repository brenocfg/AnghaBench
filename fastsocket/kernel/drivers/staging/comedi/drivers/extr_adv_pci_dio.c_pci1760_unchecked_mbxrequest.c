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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int ETIME ; 
 scalar_t__ IMB0 ; 
 scalar_t__ IMB1 ; 
 scalar_t__ IMB2 ; 
 scalar_t__ IMB3 ; 
 scalar_t__ OMB0 ; 
 scalar_t__ OMB1 ; 
 scalar_t__ OMB2 ; 
 scalar_t__ OMB3 ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pci1760_unchecked_mbxrequest(struct comedi_device *dev,
					unsigned char *omb, unsigned char *imb,
					int repeats)
{
	int cnt, tout, ok = 0;

	for (cnt = 0; cnt < repeats; cnt++) {
		outb(omb[0], dev->iobase + OMB0);
		outb(omb[1], dev->iobase + OMB1);
		outb(omb[2], dev->iobase + OMB2);
		outb(omb[3], dev->iobase + OMB3);
		for (tout = 0; tout < 251; tout++) {
			imb[2] = inb(dev->iobase + IMB2);
			if (imb[2] == omb[2]) {
				imb[0] = inb(dev->iobase + IMB0);
				imb[1] = inb(dev->iobase + IMB1);
				imb[3] = inb(dev->iobase + IMB3);
				ok = 1;
				break;
			}
			udelay(1);
		}
		if (ok)
			return 0;
	}

	comedi_error(dev, "PCI-1760 mailbox request timeout!");
	return -ETIME;
}
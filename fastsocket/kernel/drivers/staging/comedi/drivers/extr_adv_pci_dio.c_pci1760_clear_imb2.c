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
 int CMD_ClearIMB2 ; 
 scalar_t__ IMB2 ; 
 int /*<<< orphan*/  OMBCMD_RETRY ; 
 int inb (scalar_t__) ; 
 int pci1760_unchecked_mbxrequest (struct comedi_device*,unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci1760_clear_imb2(struct comedi_device *dev)
{
	unsigned char omb[4] = { 0x0, 0x0, CMD_ClearIMB2, 0x0 };
	unsigned char imb[4];
	/* check if imb2 is already clear */
	if (inb(dev->iobase + IMB2) == CMD_ClearIMB2)
		return 0;
	return pci1760_unchecked_mbxrequest(dev, omb, imb, OMBCMD_RETRY);
}
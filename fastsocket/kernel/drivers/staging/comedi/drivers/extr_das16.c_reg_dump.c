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
 scalar_t__ DAS1600_BURST ; 
 scalar_t__ DAS1600_CONV ; 
 scalar_t__ DAS1600_ENABLE ; 
 scalar_t__ DAS1600_STATUS_B ; 
 scalar_t__ DAS16_CNTR_CONTROL ; 
 scalar_t__ DAS16_CONTROL ; 
 scalar_t__ DAS16_DIO ; 
 scalar_t__ DAS16_GAIN ; 
 scalar_t__ DAS16_MUX ; 
 scalar_t__ DAS16_PACER ; 
 scalar_t__ DAS16_STATUS ; 
 int /*<<< orphan*/  DEBUG_PRINT (char*,...) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 

__attribute__((used)) static void reg_dump(struct comedi_device *dev)
{
	DEBUG_PRINT("********DAS1600 REGISTER DUMP********\n");
	DEBUG_PRINT("DAS16_MUX: %x\n", inb(dev->iobase + DAS16_MUX));
	DEBUG_PRINT("DAS16_DIO: %x\n", inb(dev->iobase + DAS16_DIO));
	DEBUG_PRINT("DAS16_STATUS: %x\n", inb(dev->iobase + DAS16_STATUS));
	DEBUG_PRINT("DAS16_CONTROL: %x\n", inb(dev->iobase + DAS16_CONTROL));
	DEBUG_PRINT("DAS16_PACER: %x\n", inb(dev->iobase + DAS16_PACER));
	DEBUG_PRINT("DAS16_GAIN: %x\n", inb(dev->iobase + DAS16_GAIN));
	DEBUG_PRINT("DAS16_CNTR_CONTROL: %x\n",
		    inb(dev->iobase + DAS16_CNTR_CONTROL));
	DEBUG_PRINT("DAS1600_CONV: %x\n", inb(dev->iobase + DAS1600_CONV));
	DEBUG_PRINT("DAS1600_BURST: %x\n", inb(dev->iobase + DAS1600_BURST));
	DEBUG_PRINT("DAS1600_ENABLE: %x\n", inb(dev->iobase + DAS1600_ENABLE));
	DEBUG_PRINT("DAS1600_STATUS_B: %x\n",
		    inb(dev->iobase + DAS1600_STATUS_B));
}
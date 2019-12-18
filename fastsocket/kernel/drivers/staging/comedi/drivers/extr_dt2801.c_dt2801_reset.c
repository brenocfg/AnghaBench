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
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 scalar_t__ DT2801_CMD ; 
 scalar_t__ DT2801_DATA ; 
 scalar_t__ DT2801_STATUS ; 
 int /*<<< orphan*/  DT_C_RESET ; 
 int /*<<< orphan*/  DT_C_STOP ; 
 unsigned int DT_S_READY ; 
 int /*<<< orphan*/  dt2801_readdata (struct comedi_device*,int*) ; 
 unsigned int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dt2801_reset(struct comedi_device *dev)
{
	int board_code = 0;
	unsigned int stat;
	int timeout;

	DPRINTK("dt2801: resetting board...\n");
	DPRINTK("fingerprint: 0x%02x 0x%02x\n", inb_p(dev->iobase),
		inb_p(dev->iobase + 1));

	/* pull random data from data port */
	inb_p(dev->iobase + DT2801_DATA);
	inb_p(dev->iobase + DT2801_DATA);
	inb_p(dev->iobase + DT2801_DATA);
	inb_p(dev->iobase + DT2801_DATA);

	DPRINTK("dt2801: stop\n");
	/* dt2801_writecmd(dev,DT_C_STOP); */
	outb_p(DT_C_STOP, dev->iobase + DT2801_CMD);

	/* dt2801_wait_for_ready(dev); */
	udelay(100);
	timeout = 10000;
	do {
		stat = inb_p(dev->iobase + DT2801_STATUS);
		if (stat & DT_S_READY)
			break;
	} while (timeout--);
	if (!timeout) {
		printk("dt2801: timeout 1 status=0x%02x\n", stat);
	}

	/* printk("dt2801: reading dummy\n"); */
	/* dt2801_readdata(dev,&board_code); */

	DPRINTK("dt2801: reset\n");
	outb_p(DT_C_RESET, dev->iobase + DT2801_CMD);
	/* dt2801_writecmd(dev,DT_C_RESET); */

	udelay(100);
	timeout = 10000;
	do {
		stat = inb_p(dev->iobase + DT2801_STATUS);
		if (stat & DT_S_READY)
			break;
	} while (timeout--);
	if (!timeout) {
		printk("dt2801: timeout 2 status=0x%02x\n", stat);
	}

	DPRINTK("dt2801: reading code\n");
	dt2801_readdata(dev, &board_code);

	DPRINTK("dt2801: ok.  code=0x%02x\n", board_code);

	return board_code;
}
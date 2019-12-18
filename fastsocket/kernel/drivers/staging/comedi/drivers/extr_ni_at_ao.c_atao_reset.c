#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {scalar_t__ cfg1; scalar_t__ cfg3; scalar_t__ cfg2; } ;

/* Variables and functions */
 scalar_t__ ATAO_2_DMATCCLR ; 
 scalar_t__ ATAO_2_INT1CLR ; 
 scalar_t__ ATAO_2_INT2CLR ; 
 scalar_t__ ATAO_82C53_CNTR1 ; 
 scalar_t__ ATAO_82C53_CNTRCMD ; 
 scalar_t__ ATAO_CFG1 ; 
 scalar_t__ ATAO_CFG2 ; 
 scalar_t__ ATAO_CFG3 ; 
 scalar_t__ ATAO_FIFO_CLEAR ; 
 int CNTRSEL0 ; 
 scalar_t__ GRP2WR ; 
 int MODESEL2 ; 
 int RWSEL0 ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void atao_reset(struct comedi_device *dev)
{
	/* This is the reset sequence described in the manual */

	devpriv->cfg1 = 0;
	outw(devpriv->cfg1, dev->iobase + ATAO_CFG1);

	outb(RWSEL0 | MODESEL2, dev->iobase + ATAO_82C53_CNTRCMD);
	outb(0x03, dev->iobase + ATAO_82C53_CNTR1);
	outb(CNTRSEL0 | RWSEL0 | MODESEL2, dev->iobase + ATAO_82C53_CNTRCMD);

	devpriv->cfg2 = 0;
	outw(devpriv->cfg2, dev->iobase + ATAO_CFG2);

	devpriv->cfg3 = 0;
	outw(devpriv->cfg3, dev->iobase + ATAO_CFG3);

	inw(dev->iobase + ATAO_FIFO_CLEAR);

	devpriv->cfg1 |= GRP2WR;
	outw(devpriv->cfg1, dev->iobase + ATAO_CFG1);

	outw(0, dev->iobase + ATAO_2_INT1CLR);
	outw(0, dev->iobase + ATAO_2_INT2CLR);
	outw(0, dev->iobase + ATAO_2_DMATCCLR);

	devpriv->cfg1 &= ~GRP2WR;
	outw(devpriv->cfg1, dev->iobase + ATAO_CFG1);
}
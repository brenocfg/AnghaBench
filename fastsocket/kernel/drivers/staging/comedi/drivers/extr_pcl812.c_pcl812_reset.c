#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_4__ {int range_correction; int old_chan_reg; int old_gain_reg; int mode_reg_int; } ;
struct TYPE_3__ {int board_type; } ;

/* Variables and functions */
 scalar_t__ PCL812_CLRINT ; 
 scalar_t__ PCL812_DA1_HI ; 
 scalar_t__ PCL812_DA1_LO ; 
 scalar_t__ PCL812_DA2_HI ; 
 scalar_t__ PCL812_DA2_LO ; 
 scalar_t__ PCL812_DO_HI ; 
 scalar_t__ PCL812_DO_LO ; 
 scalar_t__ PCL812_GAIN ; 
 scalar_t__ PCL812_MODE ; 
 scalar_t__ PCL812_MUX ; 
#define  boardA821 136 
#define  boardACL8112 135 
#define  boardACL8113 134 
#define  boardACL8216 133 
#define  boardISO813 132 
#define  boardPCL812 131 
#define  boardPCL812PG 130 
#define  boardPCL813 129 
#define  boardPCL813B 128 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  start_pacer (struct comedi_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* this_board ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pcl812_reset(struct comedi_device *dev)
{
#ifdef PCL812_EXTDEBUG
	printk("pcl812 EDBG: BGN: pcl812_reset(...)\n");
#endif
	outb(0, dev->iobase + PCL812_MUX);
	outb(0 + devpriv->range_correction, dev->iobase + PCL812_GAIN);
	devpriv->old_chan_reg = -1;	/*  invalidate chain/gain memory */
	devpriv->old_gain_reg = -1;

	switch (this_board->board_type) {
	case boardPCL812PG:
	case boardPCL812:
	case boardACL8112:
	case boardACL8216:
		outb(0, dev->iobase + PCL812_DA2_LO);
		outb(0, dev->iobase + PCL812_DA2_HI);
	case boardA821:
		outb(0, dev->iobase + PCL812_DA1_LO);
		outb(0, dev->iobase + PCL812_DA1_HI);
		start_pacer(dev, -1, 0, 0);	/*  stop 8254 */
		outb(0, dev->iobase + PCL812_DO_HI);
		outb(0, dev->iobase + PCL812_DO_LO);
		outb(devpriv->mode_reg_int | 0, dev->iobase + PCL812_MODE);
		outb(0, dev->iobase + PCL812_CLRINT);
		break;
	case boardPCL813B:
	case boardPCL813:
	case boardISO813:
	case boardACL8113:
		udelay(5);
		break;
	}
	udelay(5);
#ifdef PCL812_EXTDEBUG
	printk("pcl812 EDBG: END: pcl812_reset(...)\n");
#endif
}
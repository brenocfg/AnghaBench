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
struct TYPE_2__ {int das6402_ignoreirq; } ;
typedef  int BYTE ;

/* Variables and functions */
 int BIP ; 
 int BURSTEN ; 
 int CLRINT ; 
 int CLRXIN ; 
 int CLRXTR ; 
 int CONVSRC ; 
 int EXTEND ; 
 int FIFOHFULL ; 
 int GAIN ; 
 int INTE ; 
 int IRQ ; 
 int MHZ ; 
 int MODE ; 
 int /*<<< orphan*/  SCANL ; 
 int SEM ; 
 int TGEN ; 
 int TGSEL ; 
 int /*<<< orphan*/  das6402_setcounter (struct comedi_device*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  outw_p (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int board_init(struct comedi_device *dev)
{
	BYTE b;

	devpriv->das6402_ignoreirq = 1;

	outb(0x07, dev->iobase + 8);

	/* register 11  */
	outb_p(MODE, dev->iobase + 11);
	b = BIP | SEM | MODE | GAIN | FIFOHFULL;
	outb_p(b, dev->iobase + 11);

	/* register 8   */
	outb_p(EXTEND, dev->iobase + 8);
	b = EXTEND | MHZ;
	outb_p(b, dev->iobase + 8);
	b = MHZ | CLRINT | CLRXTR | CLRXIN;
	outb_p(b, dev->iobase + 8);

	/* register 9    */
	b = IRQ | CONVSRC | BURSTEN | INTE;
	outb_p(b, dev->iobase + 9);

	/* register 10   */
	b = TGSEL | TGEN;
	outb_p(b, dev->iobase + 10);

	b = 0x07;
	outb_p(b, dev->iobase + 8);

	das6402_setcounter(dev);

	outw_p(SCANL, dev->iobase + 2);	/* reset card fifo */

	devpriv->das6402_ignoreirq = 0;

	return 0;
}
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
typedef  int BYTE ;

/* Variables and functions */
 int C0 ; 
 int C1 ; 
 int C2 ; 
 int M0 ; 
 int M2 ; 
 int RWLH ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 

__attribute__((used)) static void das6402_setcounter(struct comedi_device *dev)
{
	BYTE p;
	unsigned short ctrlwrd;

	/* set up counter0 first, mode 0 */
	p = M0 | C0 | RWLH;
	outb_p(p, dev->iobase + 15);
	ctrlwrd = 2000;
	p = (BYTE) (0xff & ctrlwrd);
	outb_p(p, dev->iobase + 12);
	p = (BYTE) (0xff & (ctrlwrd >> 8));
	outb_p(p, dev->iobase + 12);

	/* set up counter1, mode 2 */
	p = M2 | C1 | RWLH;
	outb_p(p, dev->iobase + 15);
	ctrlwrd = 10;
	p = (BYTE) (0xff & ctrlwrd);
	outb_p(p, dev->iobase + 13);
	p = (BYTE) (0xff & (ctrlwrd >> 8));
	outb_p(p, dev->iobase + 13);

	/* set up counter1, mode 2 */
	p = M2 | C2 | RWLH;
	outb_p(p, dev->iobase + 15);
	ctrlwrd = 1000;
	p = (BYTE) (0xff & ctrlwrd);
	outb_p(p, dev->iobase + 14);
	p = (BYTE) (0xff & (ctrlwrd >> 8));
	outb_p(p, dev->iobase + 14);
}
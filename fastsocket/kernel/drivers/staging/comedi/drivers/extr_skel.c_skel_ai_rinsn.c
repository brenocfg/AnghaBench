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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int ai_bits; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int TIMEOUT ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int skel_ai_rinsn(struct comedi_device *dev, struct comedi_subdevice *s,
			 struct comedi_insn *insn, unsigned int *data)
{
	int n, i;
	unsigned int d;
	unsigned int status;

	/* a typical programming sequence */

	/* write channel to multiplexer */
	/* outw(chan,dev->iobase + SKEL_MUX); */

	/* don't wait for mux to settle */

	/* convert n samples */
	for (n = 0; n < insn->n; n++) {
		/* trigger conversion */
		/* outw(0,dev->iobase + SKEL_CONVERT); */

#define TIMEOUT 100
		/* wait for conversion to end */
		for (i = 0; i < TIMEOUT; i++) {
			status = 1;
			/* status = inb(dev->iobase + SKEL_STATUS); */
			if (status)
				break;
		}
		if (i == TIMEOUT) {
			/* printk() should be used instead of printk()
			 * whenever the code can be called from real-time. */
			printk("timeout\n");
			return -ETIMEDOUT;
		}

		/* read data */
		/* d = inw(dev->iobase + SKEL_AI_DATA); */
		d = 0;

		/* mangle the data as necessary */
		d ^= 1 << (thisboard->ai_bits - 1);

		data[n] = d;
	}

	/* return the number of samples read/written */
	return n;
}
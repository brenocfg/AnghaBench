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
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 scalar_t__ DT2821_CHANCSR ; 
 int DT2821_LLE ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  update_adcsr (unsigned int) ; 

__attribute__((used)) static void dt282x_load_changain(struct comedi_device *dev, int n,
				 unsigned int *chanlist)
{
	unsigned int i;
	unsigned int chan, range;

	outw(DT2821_LLE | (n - 1), dev->iobase + DT2821_CHANCSR);
	for (i = 0; i < n; i++) {
		chan = CR_CHAN(chanlist[i]);
		range = CR_RANGE(chanlist[i]);
		update_adcsr((range << 4) | (chan));
	}
	outw(n - 1, dev->iobase + DT2821_CHANCSR);
}
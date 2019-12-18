#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int n_chan; unsigned int* maxdata_list; int maxdata; } ;
struct comedi_device {int dummy; } ;
struct TYPE_6__ {int* caldac; } ;
struct TYPE_5__ {int n_bits; int n_chans; } ;
struct TYPE_4__ {unsigned int* caldac_maxdata_list; } ;

/* Variables and functions */
 int MAX_N_CALDACS ; 
 TYPE_3__ boardtype ; 
 int caldac_none ; 
 TYPE_2__* caldacs ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  ni_write_caldac (struct comedi_device*,int,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void caldac_setup(struct comedi_device *dev, struct comedi_subdevice *s)
{
	int i, j;
	int n_dacs;
	int n_chans = 0;
	int n_bits;
	int diffbits = 0;
	int type;
	int chan;

	type = boardtype.caldac[0];
	if (type == caldac_none)
		return;
	n_bits = caldacs[type].n_bits;
	for (i = 0; i < 3; i++) {
		type = boardtype.caldac[i];
		if (type == caldac_none)
			break;
		if (caldacs[type].n_bits != n_bits)
			diffbits = 1;
		n_chans += caldacs[type].n_chans;
	}
	n_dacs = i;
	s->n_chan = n_chans;

	if (diffbits) {
		unsigned int *maxdata_list;

		if (n_chans > MAX_N_CALDACS) {
			printk("BUG! MAX_N_CALDACS too small\n");
		}
		s->maxdata_list = maxdata_list = devpriv->caldac_maxdata_list;
		chan = 0;
		for (i = 0; i < n_dacs; i++) {
			type = boardtype.caldac[i];
			for (j = 0; j < caldacs[type].n_chans; j++) {
				maxdata_list[chan] =
				    (1 << caldacs[type].n_bits) - 1;
				chan++;
			}
		}

		for (chan = 0; chan < s->n_chan; chan++)
			ni_write_caldac(dev, i, s->maxdata_list[i] / 2);
	} else {
		type = boardtype.caldac[0];
		s->maxdata = (1 << caldacs[type].n_bits) - 1;

		for (chan = 0; chan < s->n_chan; chan++)
			ni_write_caldac(dev, i, s->maxdata / 2);
	}
}
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
struct comedi_subdevice {int n_chan; TYPE_2__** range_table_list; TYPE_1__* range_table; } ;
struct TYPE_4__ {scalar_t__ length; } ;
struct TYPE_3__ {scalar_t__ length; } ;

/* Variables and functions */
 int CR_CHAN (unsigned int) ; 
 scalar_t__ CR_RANGE (unsigned int) ; 
 int EINVAL ; 
 scalar_t__ aref_invalid (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

int check_chanlist(struct comedi_subdevice *s, int n, unsigned int *chanlist)
{
	int i;
	int chan;

	if (s->range_table) {
		for (i = 0; i < n; i++)
			if (CR_CHAN(chanlist[i]) >= s->n_chan ||
			    CR_RANGE(chanlist[i]) >= s->range_table->length
			    || aref_invalid(s, chanlist[i])) {
				printk
				    ("bad chanlist[%d]=0x%08x n_chan=%d range length=%d\n",
				     i, chanlist[i], s->n_chan,
				     s->range_table->length);
#if 0
				for (i = 0; i < n; i++)
					printk("[%d]=0x%08x\n", i, chanlist[i]);
#endif
				return -EINVAL;
			}
	} else if (s->range_table_list) {
		for (i = 0; i < n; i++) {
			chan = CR_CHAN(chanlist[i]);
			if (chan >= s->n_chan ||
			    CR_RANGE(chanlist[i]) >=
			    s->range_table_list[chan]->length
			    || aref_invalid(s, chanlist[i])) {
				printk("bad chanlist[%d]=0x%08x\n", i,
				       chanlist[i]);
				return -EINVAL;
			}
		}
	} else {
		printk("comedi: (bug) no range type list!\n");
		return -EINVAL;
	}
	return 0;
}
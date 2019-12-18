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
struct comedi_subdevice {int n_chan; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AREF_DIFF ; 
 scalar_t__ CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 int /*<<< orphan*/  CR_RANGE (unsigned int) ; 
 int /*<<< orphan*/  DPRINTK (char*,unsigned int) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,unsigned int,unsigned int,scalar_t__,...) ; 

__attribute__((used)) static int check_channel_list(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      unsigned int *chanlist, unsigned int n_chan)
{
	unsigned int chansegment[32];
	unsigned int i, nowmustbechan, seglen, segpos;

	DPRINTK("adv_pci1710 EDBG:  check_channel_list(...,%d)\n", n_chan);
	/* correct channel and range number check itself comedi/range.c */
	if (n_chan < 1) {
		comedi_error(dev, "range/channel list is empty!");
		return 0;
	}

	if (n_chan > 1) {
		chansegment[0] = chanlist[0];	/*  first channel is everytime ok */
		for (i = 1, seglen = 1; i < n_chan; i++, seglen++) {	/*  build part of chanlist */
			/*  printk("%d. %d %d\n",i,CR_CHAN(chanlist[i]),CR_RANGE(chanlist[i])); */
			if (chanlist[0] == chanlist[i])
				break;	/*  we detect loop, this must by finish */
			if (CR_CHAN(chanlist[i]) & 1)	/*  odd channel cann't by differencial */
				if (CR_AREF(chanlist[i]) == AREF_DIFF) {
					comedi_error(dev,
						     "Odd channel can't be differential input!\n");
					return 0;
				}
			nowmustbechan =
			    (CR_CHAN(chansegment[i - 1]) + 1) % s->n_chan;
			if (CR_AREF(chansegment[i - 1]) == AREF_DIFF)
				nowmustbechan = (nowmustbechan + 1) % s->n_chan;
			if (nowmustbechan != CR_CHAN(chanlist[i])) {	/*  channel list isn't continous :-( */
				printk
				    ("channel list must be continous! chanlist[%i]=%d but must be %d or %d!\n",
				     i, CR_CHAN(chanlist[i]), nowmustbechan,
				     CR_CHAN(chanlist[0]));
				return 0;
			}
			chansegment[i] = chanlist[i];	/*  well, this is next correct channel in list */
		}

		for (i = 0, segpos = 0; i < n_chan; i++) {	/*  check whole chanlist */
			/* printk("%d %d=%d %d\n",CR_CHAN(chansegment[i%seglen]),CR_RANGE(chansegment[i%seglen]),CR_CHAN(chanlist[i]),CR_RANGE(chanlist[i])); */
			if (chanlist[i] != chansegment[i % seglen]) {
				printk
				    ("bad channel, reference or range number! chanlist[%i]=%d,%d,%d and not %d,%d,%d!\n",
				     i, CR_CHAN(chansegment[i]),
				     CR_RANGE(chansegment[i]),
				     CR_AREF(chansegment[i]),
				     CR_CHAN(chanlist[i % seglen]),
				     CR_RANGE(chanlist[i % seglen]),
				     CR_AREF(chansegment[i % seglen]));
				return 0;	/*  chan/gain list is strange */
			}
		}
	} else {
		seglen = 1;
	}
	return seglen;
}
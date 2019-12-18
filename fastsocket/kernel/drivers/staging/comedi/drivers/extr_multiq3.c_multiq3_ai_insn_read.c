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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 scalar_t__ MULTIQ3_AD_CS ; 
 int MULTIQ3_AD_MUX_EN ; 
 scalar_t__ MULTIQ3_CONTROL ; 
 int MULTIQ3_CONTROL_MUST ; 
 scalar_t__ MULTIQ3_STATUS ; 
 int MULTIQ3_STATUS_EOC ; 
 int MULTIQ3_STATUS_EOC_I ; 
 int MULTIQ3_TIMEOUT ; 
 unsigned int inb (scalar_t__) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int multiq3_ai_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	int i, n;
	int chan;
	unsigned int hi, lo;

	chan = CR_CHAN(insn->chanspec);
	outw(MULTIQ3_CONTROL_MUST | MULTIQ3_AD_MUX_EN | (chan << 3),
	     dev->iobase + MULTIQ3_CONTROL);

	for (i = 0; i < MULTIQ3_TIMEOUT; i++) {
		if (inw(dev->iobase + MULTIQ3_STATUS) & MULTIQ3_STATUS_EOC)
			break;
	}
	if (i == MULTIQ3_TIMEOUT)
		return -ETIMEDOUT;

	for (n = 0; n < insn->n; n++) {
		outw(0, dev->iobase + MULTIQ3_AD_CS);
		for (i = 0; i < MULTIQ3_TIMEOUT; i++) {
			if (inw(dev->iobase +
				MULTIQ3_STATUS) & MULTIQ3_STATUS_EOC_I)
				break;
		}
		if (i == MULTIQ3_TIMEOUT)
			return -ETIMEDOUT;

		hi = inb(dev->iobase + MULTIQ3_AD_CS);
		lo = inb(dev->iobase + MULTIQ3_AD_CS);
		data[n] = (((hi << 8) | lo) + 0x1000) & 0x1fff;
	}

	return n;
}
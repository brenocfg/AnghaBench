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
 int MULTIQ3_AD_MUX_EN ; 
 int /*<<< orphan*/  MULTIQ3_BP_RESET ; 
 scalar_t__ MULTIQ3_CONTROL ; 
 int MULTIQ3_CONTROL_MUST ; 
 scalar_t__ MULTIQ3_ENC_CONTROL ; 
 scalar_t__ MULTIQ3_ENC_DATA ; 
 int /*<<< orphan*/  MULTIQ3_TRSFRCNTR_OL ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int multiq3_encoder_insn_read(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	int n;
	int chan = CR_CHAN(insn->chanspec);
	int control = MULTIQ3_CONTROL_MUST | MULTIQ3_AD_MUX_EN | (chan << 3);

	for (n = 0; n < insn->n; n++) {
		int value;
		outw(control, dev->iobase + MULTIQ3_CONTROL);
		outb(MULTIQ3_BP_RESET, dev->iobase + MULTIQ3_ENC_CONTROL);
		outb(MULTIQ3_TRSFRCNTR_OL, dev->iobase + MULTIQ3_ENC_CONTROL);
		value = inb(dev->iobase + MULTIQ3_ENC_DATA);
		value |= (inb(dev->iobase + MULTIQ3_ENC_DATA) << 8);
		value |= (inb(dev->iobase + MULTIQ3_ENC_DATA) << 16);
		data[n] = (value + 0x800000) & 0xffffff;
	}

	return n;
}
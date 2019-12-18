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
struct local_info_t {scalar_t__ stop; } ;
struct comedi_subdevice {scalar_t__ private; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ DAQP_AUX ; 
 scalar_t__ DAQP_DA ; 
 int EIO ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int daqp_ao_insn_write(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
	struct local_info_t *local = (struct local_info_t *)s->private;
	int d;
	unsigned int chan;

	if (local->stop) {
		return -EIO;
	}

	chan = CR_CHAN(insn->chanspec);
	d = data[0];
	d &= 0x0fff;
	d ^= 0x0800;		/* Flip the sign */
	d |= chan << 12;

	/* Make sure D/A update mode is direct update */
	outb(0, dev->iobase + DAQP_AUX);

	outw(d, dev->iobase + DAQP_DA);

	return 1;
}
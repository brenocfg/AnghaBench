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
struct comedi_subdevice {int io_bits; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ me_regbase; int /*<<< orphan*/  control_2; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENABLE_PORT_A ; 
 int /*<<< orphan*/  ENABLE_PORT_B ; 
 scalar_t__ ME_CONTROL_2 ; 
 TYPE_1__* dev_private ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int me_dio_insn_config(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
	int bits;
	int mask = 1 << CR_CHAN(insn->chanspec);

	/* calculate port */
	if (mask & 0x0000ffff) {	/* Port A in use */
		bits = 0x0000ffff;

		/* Enable Port A */
		dev_private->control_2 |= ENABLE_PORT_A;
		writew(dev_private->control_2,
		       dev_private->me_regbase + ME_CONTROL_2);
	} else {		/* Port B in use */

		bits = 0xffff0000;

		/* Enable Port B */
		dev_private->control_2 |= ENABLE_PORT_B;
		writew(dev_private->control_2,
		       dev_private->me_regbase + ME_CONTROL_2);
	}

	if (data[0]) {
		/* Config port as output */
		s->io_bits |= bits;
	} else {
		/* Config port as input */
		s->io_bits &= ~bits;
	}

	return 1;
}
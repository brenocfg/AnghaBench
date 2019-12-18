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
struct dio200_subdev_intr {unsigned int valid_isns; int /*<<< orphan*/  iobase; scalar_t__ has_int_sce; } ;
struct comedi_subdevice {struct dio200_subdev_intr* private; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dio200_subdev_intr_insn_bits(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn, unsigned int *data)
{
	struct dio200_subdev_intr *subpriv = s->private;

	if (subpriv->has_int_sce) {
		/* Just read the interrupt status register.  */
		data[1] = inb(subpriv->iobase) & subpriv->valid_isns;
	} else {
		/* No interrupt status register. */
		data[0] = 0;
	}

	return 2;
}
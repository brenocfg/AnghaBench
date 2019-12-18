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
struct comedi_insn {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DAQP_DIGITAL_IO ; 
 int EIO ; 
 unsigned int inb (scalar_t__) ; 

__attribute__((used)) static int daqp_di_insn_read(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn, unsigned int *data)
{
	struct local_info_t *local = (struct local_info_t *)s->private;

	if (local->stop) {
		return -EIO;
	}

	data[0] = inb(dev->iobase + DAQP_DIGITAL_IO);

	return 1;
}
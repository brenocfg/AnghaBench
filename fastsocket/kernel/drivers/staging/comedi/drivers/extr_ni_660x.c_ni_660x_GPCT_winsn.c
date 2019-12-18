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
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int ni_tio_winsn (int /*<<< orphan*/ ,struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  subdev_to_counter (struct comedi_subdevice*) ; 

__attribute__((used)) static int ni_660x_GPCT_winsn(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
	return ni_tio_winsn(subdev_to_counter(s), insn, data);
}
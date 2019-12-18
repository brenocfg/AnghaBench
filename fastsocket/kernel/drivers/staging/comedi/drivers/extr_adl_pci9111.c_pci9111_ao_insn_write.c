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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned int ao_readback; } ;

/* Variables and functions */
 TYPE_1__* dev_private ; 
 int /*<<< orphan*/  pci9111_ao_set_data (unsigned int) ; 

__attribute__((used)) static int
pci9111_ao_insn_write(struct comedi_device *dev,
		      struct comedi_subdevice *s, struct comedi_insn *insn,
		      unsigned int *data)
{
	int i;

	for (i = 0; i < insn->n; i++) {
		pci9111_ao_set_data(data[i]);
		dev_private->ao_readback = data[i];
	}

	return i;
}
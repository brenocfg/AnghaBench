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
struct comedi_subdevice {unsigned int state; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ io_addr; } ;

/* Variables and functions */
 scalar_t__ ICP_MULTI_DI ; 
 scalar_t__ ICP_MULTI_DO ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int icp_multi_insn_bits_do(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn, unsigned int *data)
{
#ifdef ICP_MULTI_EXTDEBUG
	printk("icp multi EDBG: BGN: icp_multi_insn_bits_do(...)\n");
#endif

	if (data[0]) {
		s->state &= ~data[0];
		s->state |= (data[0] & data[1]);

		printk("Digital outputs = %4x \n", s->state);

		writew(s->state, devpriv->io_addr + ICP_MULTI_DO);
	}

	data[1] = readw(devpriv->io_addr + ICP_MULTI_DI);

#ifdef ICP_MULTI_EXTDEBUG
	printk("icp multi EDBG: END: icp_multi_insn_bits_do(...)\n");
#endif
	return 2;
}
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
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned int* ao_readback; } ;

/* Variables and functions */
 size_t CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DT_C_WRITE_DAIM ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  dt2801_writecmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt2801_writedata (struct comedi_device*,size_t) ; 
 int /*<<< orphan*/  dt2801_writedata2 (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static int dt2801_ao_insn_write(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	dt2801_writecmd(dev, DT_C_WRITE_DAIM);
	dt2801_writedata(dev, CR_CHAN(insn->chanspec));
	dt2801_writedata2(dev, data[0]);

	devpriv->ao_readback[CR_CHAN(insn->chanspec)] = data[0];

	return 1;
}
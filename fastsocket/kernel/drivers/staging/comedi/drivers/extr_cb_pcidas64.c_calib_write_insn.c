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
struct TYPE_2__ {unsigned int* caldac_state; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caldac_write (struct comedi_device*,int,unsigned int) ; 
 TYPE_1__* priv (struct comedi_device*) ; 

__attribute__((used)) static int calib_write_insn(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
	int channel = CR_CHAN(insn->chanspec);

	/* return immediately if setting hasn't changed, since
	 * programming these things is slow */
	if (priv(dev)->caldac_state[channel] == data[0])
		return 1;

	caldac_write(dev, channel, data[0]);

	return 1;
}
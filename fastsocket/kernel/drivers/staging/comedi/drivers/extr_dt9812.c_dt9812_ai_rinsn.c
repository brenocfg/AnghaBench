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
typedef  unsigned int u16 ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT9812_GAIN_1 ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  dt9812_analog_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dt9812_ai_rinsn(struct comedi_device *dev,
			   struct comedi_subdevice *s, struct comedi_insn *insn,
			   unsigned int *data)
{
	int n;

	for (n = 0; n < insn->n; n++) {
		u16 value = 0;

		dt9812_analog_in(devpriv->slot, insn->chanspec, &value,
				 DT9812_GAIN_1);
		data[n] = value;
	}
	return n;
}
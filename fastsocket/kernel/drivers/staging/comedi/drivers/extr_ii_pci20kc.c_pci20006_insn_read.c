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
struct TYPE_2__ {unsigned int* last_data; } ;
union pci20xxx_subdev_private {TYPE_1__ pci20006; } ;
struct comedi_subdevice {union pci20xxx_subdev_private* private; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 size_t CR_CHAN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci20006_insn_read(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
	union pci20xxx_subdev_private *sdp = s->private;

	data[0] = sdp->pci20006.last_data[CR_CHAN(insn->chanspec)];

	return 1;
}
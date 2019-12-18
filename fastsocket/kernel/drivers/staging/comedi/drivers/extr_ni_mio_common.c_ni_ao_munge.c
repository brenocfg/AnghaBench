#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_3__ {unsigned int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {TYPE_1__ cmd; } ;
struct TYPE_4__ {int aobits; scalar_t__ ao_unipolar; } ;

/* Variables and functions */
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 TYPE_2__ boardtype ; 
 short cpu_to_le16 (short) ; 

__attribute__((used)) static void ni_ao_munge(struct comedi_device *dev, struct comedi_subdevice *s,
			void *data, unsigned int num_bytes,
			unsigned int chan_index)
{
	struct comedi_async *async = s->async;
	unsigned int range;
	unsigned int i;
	unsigned int offset;
	unsigned int length = num_bytes / sizeof(short);
	short *array = data;

	offset = 1 << (boardtype.aobits - 1);
	for (i = 0; i < length; i++) {
		range = CR_RANGE(async->cmd.chanlist[chan_index]);
		if (boardtype.ao_unipolar == 0 || (range & 1) == 0)
			array[i] -= offset;
#ifdef PCIDMA
		array[i] = cpu_to_le16(array[i]);
#endif
		chan_index++;
		chan_index %= async->cmd.chanlist_len;
	}
}
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
struct jr3_pci_subdev_private {scalar_t__ state; TYPE_2__* channel; } ;
struct comedi_subdevice {struct jr3_pci_subdev_private* private; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  serial_no; int /*<<< orphan*/  model_no; TYPE_1__* filter; int /*<<< orphan*/  errors; } ;
struct TYPE_3__ {int /*<<< orphan*/  v2; int /*<<< orphan*/  v1; int /*<<< orphan*/  mz; int /*<<< orphan*/  my; int /*<<< orphan*/  mx; int /*<<< orphan*/  fz; int /*<<< orphan*/  fy; int /*<<< orphan*/  fx; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int get_s16 (int /*<<< orphan*/ *) ; 
 unsigned int get_u16 (int /*<<< orphan*/ *) ; 
 unsigned int sensor_change ; 
 scalar_t__ state_jr3_done ; 
 scalar_t__ state_jr3_poll ; 
 unsigned int watch_dog ; 
 unsigned int watch_dog2 ; 

__attribute__((used)) static int jr3_pci_ai_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	int result;
	struct jr3_pci_subdev_private *p;
	int channel;

	p = s->private;
	channel = CR_CHAN(insn->chanspec);
	if (p == NULL || channel > 57) {
		result = -EINVAL;
	} else {
		int i;

		result = insn->n;
		if (p->state != state_jr3_done ||
		    (get_u16(&p->channel->errors) & (watch_dog | watch_dog2 |
						     sensor_change))) {
			/* No sensor or sensor changed */
			if (p->state == state_jr3_done) {
				/* Restart polling */
				p->state = state_jr3_poll;
			}
			result = -EAGAIN;
		}
		for (i = 0; i < insn->n; i++) {
			if (channel < 56) {
				int axis, filter;

				axis = channel % 8;
				filter = channel / 8;
				if (p->state != state_jr3_done) {
					data[i] = 0;
				} else {
					int F = 0;
					switch (axis) {
					case 0:{
							F = get_s16
							    (&p->channel->filter
							     [filter].fx);
						}
						break;
					case 1:{
							F = get_s16
							    (&p->channel->filter
							     [filter].fy);
						}
						break;
					case 2:{
							F = get_s16
							    (&p->channel->filter
							     [filter].fz);
						}
						break;
					case 3:{
							F = get_s16
							    (&p->channel->filter
							     [filter].mx);
						}
						break;
					case 4:{
							F = get_s16
							    (&p->channel->filter
							     [filter].my);
						}
						break;
					case 5:{
							F = get_s16
							    (&p->channel->filter
							     [filter].mz);
						}
						break;
					case 6:{
							F = get_s16
							    (&p->channel->filter
							     [filter].v1);
						}
						break;
					case 7:{
							F = get_s16
							    (&p->channel->filter
							     [filter].v2);
						}
						break;
					}
					data[i] = F + 0x4000;
				}
			} else if (channel == 56) {
				if (p->state != state_jr3_done) {
					data[i] = 0;
				} else {
					data[i] =
					    get_u16(&p->channel->model_no);
				}
			} else if (channel == 57) {
				if (p->state != state_jr3_done) {
					data[i] = 0;
				} else {
					data[i] =
					    get_u16(&p->channel->serial_no);
				}
			}
		}
	}
	return result;
}
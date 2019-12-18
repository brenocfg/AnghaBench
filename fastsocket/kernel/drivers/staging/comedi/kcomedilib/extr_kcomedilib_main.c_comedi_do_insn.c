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
struct timeval {int tv_sec; int tv_usec; } ;
struct comedi_subdevice {scalar_t__ type; int (* insn_read ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int*) ;int (* insn_write ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int*) ;int (* insn_bits ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int*) ;int (* insn_config ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int*) ;int /*<<< orphan*/ * busy; TYPE_1__* async; } ;
struct comedi_insn {int insn; int* data; int n; scalar_t__ subdev; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ n_subdevices; struct comedi_subdevice* subdevices; } ;
struct TYPE_2__ {int (* inttrig ) (struct comedi_device*,struct comedi_subdevice*,int) ;} ;

/* Variables and functions */
 scalar_t__ COMEDI_SUBD_UNUSED ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
#define  INSN_BITS 134 
#define  INSN_CONFIG 133 
#define  INSN_GTOD 132 
#define  INSN_INTTRIG 131 
 int INSN_MASK_SPECIAL ; 
#define  INSN_READ 130 
#define  INSN_WAIT 129 
#define  INSN_WRITE 128 
 int check_chanlist (struct comedi_subdevice*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int stub1 (struct comedi_device*,struct comedi_subdevice*,int) ; 
 int stub2 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int*) ; 
 int stub3 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int*) ; 
 int stub4 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int*) ; 
 int stub5 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int comedi_do_insn(void *d, struct comedi_insn *insn)
{
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s;
	int ret = 0;

	if (insn->insn & INSN_MASK_SPECIAL) {
		switch (insn->insn) {
		case INSN_GTOD:
			{
				struct timeval tv;

				do_gettimeofday(&tv);
				insn->data[0] = tv.tv_sec;
				insn->data[1] = tv.tv_usec;
				ret = 2;

				break;
			}
		case INSN_WAIT:
			/* XXX isn't the value supposed to be nanosecs? */
			if (insn->n != 1 || insn->data[0] >= 100) {
				ret = -EINVAL;
				break;
			}
			udelay(insn->data[0]);
			ret = 1;
			break;
		case INSN_INTTRIG:
			if (insn->n != 1) {
				ret = -EINVAL;
				break;
			}
			if (insn->subdev >= dev->n_subdevices) {
				printk("%d not usable subdevice\n",
				       insn->subdev);
				ret = -EINVAL;
				break;
			}
			s = dev->subdevices + insn->subdev;
			if (!s->async) {
				printk("no async\n");
				ret = -EINVAL;
				break;
			}
			if (!s->async->inttrig) {
				printk("no inttrig\n");
				ret = -EAGAIN;
				break;
			}
			ret = s->async->inttrig(dev, s, insn->data[0]);
			if (ret >= 0)
				ret = 1;
			break;
		default:
			ret = -EINVAL;
		}
	} else {
		/* a subdevice instruction */
		if (insn->subdev >= dev->n_subdevices) {
			ret = -EINVAL;
			goto error;
		}
		s = dev->subdevices + insn->subdev;

		if (s->type == COMEDI_SUBD_UNUSED) {
			printk("%d not useable subdevice\n", insn->subdev);
			ret = -EIO;
			goto error;
		}

		/* XXX check lock */

		ret = check_chanlist(s, 1, &insn->chanspec);
		if (ret < 0) {
			printk("bad chanspec\n");
			ret = -EINVAL;
			goto error;
		}

		if (s->busy) {
			ret = -EBUSY;
			goto error;
		}
		s->busy = d;

		switch (insn->insn) {
		case INSN_READ:
			ret = s->insn_read(dev, s, insn, insn->data);
			break;
		case INSN_WRITE:
			ret = s->insn_write(dev, s, insn, insn->data);
			break;
		case INSN_BITS:
			ret = s->insn_bits(dev, s, insn, insn->data);
			break;
		case INSN_CONFIG:
			/* XXX should check instruction length */
			ret = s->insn_config(dev, s, insn, insn->data);
			break;
		default:
			ret = -EINVAL;
			break;
		}

		s->busy = NULL;
	}
	if (ret < 0)
		goto error;
#if 0
	/* XXX do we want this? -- abbotti #if'ed it out for now. */
	if (ret != insn->n) {
		printk("BUG: result of insn != insn.n\n");
		ret = -EINVAL;
		goto error;
	}
#endif
error:

	return ret;
}
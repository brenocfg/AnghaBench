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
struct timeval {unsigned int tv_sec; unsigned int tv_usec; } ;
struct comedi_subdevice {scalar_t__ type; void* lock; int (* busy ) (struct comedi_device*,struct comedi_insn*,unsigned int*,void*) ;int (* insn_read ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ;unsigned int* maxdata_list; unsigned int maxdata; int (* insn_write ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ;int (* insn_bits ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ;int (* insn_config ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ;TYPE_1__* async; } ;
struct comedi_insn {int insn; int n; scalar_t__ subdev; int /*<<< orphan*/  chanspec; int /*<<< orphan*/ * data; } ;
struct comedi_device {scalar_t__ n_subdevices; struct comedi_subdevice* subdevices; } ;
struct TYPE_2__ {int (* inttrig ) (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ COMEDI_SUBD_UNUSED ; 
 size_t CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EACCES ; 
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
 int check_insn_config_length (struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int stub1 (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int stub2 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int stub3 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int stub4 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int stub5 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 

__attribute__((used)) static int parse_insn(struct comedi_device *dev, struct comedi_insn *insn,
		      unsigned int *data, void *file)
{
	struct comedi_subdevice *s;
	int ret = 0;
	int i;

	if (insn->insn & INSN_MASK_SPECIAL) {
		/* a non-subdevice instruction */

		switch (insn->insn) {
		case INSN_GTOD:
			{
				struct timeval tv;

				if (insn->n != 2) {
					ret = -EINVAL;
					break;
				}

				do_gettimeofday(&tv);
				data[0] = tv.tv_sec;
				data[1] = tv.tv_usec;
				ret = 2;

				break;
			}
		case INSN_WAIT:
			if (insn->n != 1 || data[0] >= 100000) {
				ret = -EINVAL;
				break;
			}
			udelay(data[0] / 1000);
			ret = 1;
			break;
		case INSN_INTTRIG:
			if (insn->n != 1) {
				ret = -EINVAL;
				break;
			}
			if (insn->subdev >= dev->n_subdevices) {
				DPRINTK("%d not usable subdevice\n",
					insn->subdev);
				ret = -EINVAL;
				break;
			}
			s = dev->subdevices + insn->subdev;
			if (!s->async) {
				DPRINTK("no async\n");
				ret = -EINVAL;
				break;
			}
			if (!s->async->inttrig) {
				DPRINTK("no inttrig\n");
				ret = -EAGAIN;
				break;
			}
			ret = s->async->inttrig(dev, s, insn->data[0]);
			if (ret >= 0)
				ret = 1;
			break;
		default:
			DPRINTK("invalid insn\n");
			ret = -EINVAL;
			break;
		}
	} else {
		/* a subdevice instruction */
		unsigned int maxdata;

		if (insn->subdev >= dev->n_subdevices) {
			DPRINTK("subdevice %d out of range\n", insn->subdev);
			ret = -EINVAL;
			goto out;
		}
		s = dev->subdevices + insn->subdev;

		if (s->type == COMEDI_SUBD_UNUSED) {
			DPRINTK("%d not usable subdevice\n", insn->subdev);
			ret = -EIO;
			goto out;
		}

		/* are we locked? (ioctl lock) */
		if (s->lock && s->lock != file) {
			DPRINTK("device locked\n");
			ret = -EACCES;
			goto out;
		}

		ret = check_chanlist(s, 1, &insn->chanspec);
		if (ret < 0) {
			ret = -EINVAL;
			DPRINTK("bad chanspec\n");
			goto out;
		}

		if (s->busy) {
			ret = -EBUSY;
			goto out;
		}
		/* This looks arbitrary.  It is. */
		s->busy = &parse_insn;
		switch (insn->insn) {
		case INSN_READ:
			ret = s->insn_read(dev, s, insn, data);
			break;
		case INSN_WRITE:
			maxdata = s->maxdata_list
			    ? s->maxdata_list[CR_CHAN(insn->chanspec)]
			    : s->maxdata;
			for (i = 0; i < insn->n; ++i) {
				if (data[i] > maxdata) {
					ret = -EINVAL;
					DPRINTK("bad data value(s)\n");
					break;
				}
			}
			if (ret == 0)
				ret = s->insn_write(dev, s, insn, data);
			break;
		case INSN_BITS:
			if (insn->n != 2) {
				ret = -EINVAL;
				break;
			}
			ret = s->insn_bits(dev, s, insn, data);
			break;
		case INSN_CONFIG:
			ret = check_insn_config_length(insn, data);
			if (ret)
				break;
			ret = s->insn_config(dev, s, insn, data);
			break;
		default:
			ret = -EINVAL;
			break;
		}

		s->busy = NULL;
	}

out:
	return ret;
}
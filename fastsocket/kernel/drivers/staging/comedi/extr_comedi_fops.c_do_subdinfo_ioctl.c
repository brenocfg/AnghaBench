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
struct comedi_subdinfo {int range_type; int /*<<< orphan*/  settling_time_0; int /*<<< orphan*/  insn_bits_support; int /*<<< orphan*/  subd_flags; int /*<<< orphan*/  flags; int /*<<< orphan*/  maxdata; int /*<<< orphan*/  len_chanlist; int /*<<< orphan*/  timer_type; int /*<<< orphan*/  n_chan; int /*<<< orphan*/  type; } ;
struct comedi_subdevice {void* busy; void* lock; int /*<<< orphan*/  settling_time_0; int /*<<< orphan*/ * insn_bits; scalar_t__ do_cmd; scalar_t__ range_table_list; scalar_t__ flaglist; scalar_t__ maxdata_list; int /*<<< orphan*/  maxdata; int /*<<< orphan*/  flags; TYPE_1__* range_table; int /*<<< orphan*/  len_chanlist; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  n_chan; int /*<<< orphan*/  type; } ;
struct comedi_device {int n_subdevices; struct comedi_subdevice* subdevices; } ;
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUPPORTED ; 
 int /*<<< orphan*/  COMEDI_UNSUPPORTED ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SDF_BUSY ; 
 int /*<<< orphan*/  SDF_BUSY_OWNER ; 
 int /*<<< orphan*/  SDF_CMD ; 
 int /*<<< orphan*/  SDF_FLAGS ; 
 int /*<<< orphan*/  SDF_LOCKED ; 
 int /*<<< orphan*/  SDF_LOCK_OWNER ; 
 int /*<<< orphan*/  SDF_MAXDATA ; 
 int /*<<< orphan*/  SDF_RANGETYPE ; 
 int /*<<< orphan*/  SDF_RUNNING ; 
 int SRF_RUNNING ; 
 int /*<<< orphan*/  TIMER_nanosec ; 
 int comedi_get_subdevice_runflags (struct comedi_subdevice*) ; 
 int copy_to_user (struct comedi_subdinfo*,struct comedi_subdinfo*,int) ; 
 int /*<<< orphan*/  insn_inval ; 
 struct comedi_subdinfo* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct comedi_subdinfo*) ; 

__attribute__((used)) static int do_subdinfo_ioctl(struct comedi_device *dev,
			     struct comedi_subdinfo *arg, void *file)
{
	int ret, i;
	struct comedi_subdinfo *tmp, *us;
	struct comedi_subdevice *s;

	tmp =
	    kcalloc(dev->n_subdevices, sizeof(struct comedi_subdinfo),
		    GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	/* fill subdinfo structs */
	for (i = 0; i < dev->n_subdevices; i++) {
		s = dev->subdevices + i;
		us = tmp + i;

		us->type = s->type;
		us->n_chan = s->n_chan;
		us->subd_flags = s->subdev_flags;
		if (comedi_get_subdevice_runflags(s) & SRF_RUNNING)
			us->subd_flags |= SDF_RUNNING;
#define TIMER_nanosec 5		/* backwards compatibility */
		us->timer_type = TIMER_nanosec;
		us->len_chanlist = s->len_chanlist;
		us->maxdata = s->maxdata;
		if (s->range_table) {
			us->range_type =
			    (i << 24) | (0 << 16) | (s->range_table->length);
		} else {
			us->range_type = 0;	/* XXX */
		}
		us->flags = s->flags;

		if (s->busy)
			us->subd_flags |= SDF_BUSY;
		if (s->busy == file)
			us->subd_flags |= SDF_BUSY_OWNER;
		if (s->lock)
			us->subd_flags |= SDF_LOCKED;
		if (s->lock == file)
			us->subd_flags |= SDF_LOCK_OWNER;
		if (!s->maxdata && s->maxdata_list)
			us->subd_flags |= SDF_MAXDATA;
		if (s->flaglist)
			us->subd_flags |= SDF_FLAGS;
		if (s->range_table_list)
			us->subd_flags |= SDF_RANGETYPE;
		if (s->do_cmd)
			us->subd_flags |= SDF_CMD;

		if (s->insn_bits != &insn_inval)
			us->insn_bits_support = COMEDI_SUPPORTED;
		else
			us->insn_bits_support = COMEDI_UNSUPPORTED;

		us->settling_time_0 = s->settling_time_0;
	}

	ret = copy_to_user(arg, tmp,
			   dev->n_subdevices * sizeof(struct comedi_subdinfo));

	kfree(tmp);

	return ret ? -EFAULT : 0;
}
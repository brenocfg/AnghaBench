#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_6__ {unsigned int filter_interval; int* filter_enable; TYPE_1__* mite; } ;
struct TYPE_5__ {unsigned int base_port; } ;
struct TYPE_4__ {scalar_t__ daq_io_addr; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ Filter_Enable (unsigned int const) ; 
 scalar_t__ Filter_Interval ; 
 unsigned int INSN_CONFIG_FILTER ; 
 unsigned int const ni_65xx_channels_per_port ; 
 unsigned int ni_65xx_port_by_channel (unsigned int const) ; 
 TYPE_3__* private (struct comedi_device*) ; 
 TYPE_2__* sprivate (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int ni_65xx_config_filter(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
	const unsigned chan = CR_CHAN(insn->chanspec);
	const unsigned port =
	    sprivate(s)->base_port + ni_65xx_port_by_channel(chan);

	if (data[0] != INSN_CONFIG_FILTER)
		return -EINVAL;
	if (data[1]) {
		static const unsigned filter_resolution_ns = 200;
		static const unsigned max_filter_interval = 0xfffff;
		unsigned interval =
		    (data[1] +
		     (filter_resolution_ns / 2)) / filter_resolution_ns;
		if (interval > max_filter_interval)
			interval = max_filter_interval;
		data[1] = interval * filter_resolution_ns;

		if (interval != private(dev)->filter_interval) {
			writeb(interval,
			       private(dev)->mite->daq_io_addr +
			       Filter_Interval);
			private(dev)->filter_interval = interval;
		}

		private(dev)->filter_enable[port] |=
		    1 << (chan % ni_65xx_channels_per_port);
	} else {
		private(dev)->filter_enable[port] &=
		    ~(1 << (chan % ni_65xx_channels_per_port));
	}

	writeb(private(dev)->filter_enable[port],
	       private(dev)->mite->daq_io_addr + Filter_Enable(port));

	return 2;
}
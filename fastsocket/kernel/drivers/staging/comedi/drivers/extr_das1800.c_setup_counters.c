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
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {int scan_begin_src; int convert_src; int flags; scalar_t__ stop_src; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/  convert_arg; } ;
struct TYPE_2__ {int /*<<< orphan*/  divisor2; int /*<<< orphan*/  divisor1; } ;

/* Variables and functions */
 scalar_t__ DAS1800_COUNTER ; 
 int /*<<< orphan*/  TIMER_BASE ; 
 scalar_t__ TRIG_EXT ; 
#define  TRIG_FOLLOW 129 
 int TRIG_ROUND_MASK ; 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  das1800_set_frequency (struct comedi_device*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer_2div (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i8254_load (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_counters(struct comedi_device *dev, struct comedi_cmd cmd)
{
	/*  setup cascaded counters for conversion/scan frequency */
	switch (cmd.scan_begin_src) {
	case TRIG_FOLLOW:	/*  not in burst mode */
		if (cmd.convert_src == TRIG_TIMER) {
			/* set conversion frequency */
			i8253_cascade_ns_to_timer_2div(TIMER_BASE,
						       &(devpriv->divisor1),
						       &(devpriv->divisor2),
						       &(cmd.convert_arg),
						       cmd.
						       flags & TRIG_ROUND_MASK);
			if (das1800_set_frequency(dev) < 0) {
				return -1;
			}
		}
		break;
	case TRIG_TIMER:	/*  in burst mode */
		/* set scan frequency */
		i8253_cascade_ns_to_timer_2div(TIMER_BASE, &(devpriv->divisor1),
					       &(devpriv->divisor2),
					       &(cmd.scan_begin_arg),
					       cmd.flags & TRIG_ROUND_MASK);
		if (das1800_set_frequency(dev) < 0) {
			return -1;
		}
		break;
	default:
		break;
	}

	/*  setup counter 0 for 'about triggering' */
	if (cmd.stop_src == TRIG_EXT) {
		/*  load counter 0 in mode 0 */
		i8254_load(dev->iobase + DAS1800_COUNTER, 0, 0, 1, 0);
	}

	return 0;
}
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
typedef  unsigned int uint32_t ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {int scan_begin_src; unsigned int scan_begin_arg; } ;
struct TYPE_3__ {unsigned int divisor; } ;
struct TYPE_4__ {TYPE_1__ ext_clock; } ;

/* Variables and functions */
 unsigned int TIMER_BASE ; 
#define  TRIG_OTHER 129 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* priv (struct comedi_device*) ; 

__attribute__((used)) static uint32_t ai_convert_counter_4020(struct comedi_device *dev,
					struct comedi_cmd *cmd)
{
	unsigned int divisor;

	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		divisor = cmd->scan_begin_arg / TIMER_BASE;
		break;
	case TRIG_OTHER:
		divisor = priv(dev)->ext_clock.divisor;
		break;
	default:		/*  should never happen */
		comedi_error(dev, "bug! failed to set ai pacing!");
		divisor = 1000;
		break;
	}

	/*  supposed to load counter with desired divisor minus 2 for 4020 */
	return divisor - 2;
}
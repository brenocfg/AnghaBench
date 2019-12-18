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
struct comedi_device {int dummy; } ;
struct comedi_cmd {scalar_t__ scan_begin_src; } ;
struct TYPE_3__ {int chanspec; } ;
struct TYPE_4__ {scalar_t__ main_iobase; int /*<<< orphan*/  hw_config_bits; TYPE_1__ ext_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNC_CLOCK_4020_BITS ; 
 scalar_t__ CR_CHAN (int) ; 
 int /*<<< orphan*/  EXT_CLOCK_4020_BITS ; 
 scalar_t__ HW_CONFIG_REG ; 
 int /*<<< orphan*/  INTERNAL_CLOCK_4020_BITS ; 
 int /*<<< orphan*/  MASTER_CLOCK_4020_MASK ; 
 scalar_t__ TRIG_OTHER ; 
 TYPE_2__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void select_master_clock_4020(struct comedi_device *dev,
				     const struct comedi_cmd *cmd)
{
	/*  select internal/external master clock */
	priv(dev)->hw_config_bits &= ~MASTER_CLOCK_4020_MASK;
	if (cmd->scan_begin_src == TRIG_OTHER) {
		int chanspec = priv(dev)->ext_clock.chanspec;

		if (CR_CHAN(chanspec))
			priv(dev)->hw_config_bits |= BNC_CLOCK_4020_BITS;
		else
			priv(dev)->hw_config_bits |= EXT_CLOCK_4020_BITS;
	} else {
		priv(dev)->hw_config_bits |= INTERNAL_CLOCK_4020_BITS;
	}
	writew(priv(dev)->hw_config_bits,
	       priv(dev)->main_iobase + HW_CONFIG_REG);
}
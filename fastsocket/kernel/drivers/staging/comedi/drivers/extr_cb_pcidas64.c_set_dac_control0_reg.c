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
struct comedi_device {int dummy; } ;
struct comedi_cmd {scalar_t__ start_src; int start_arg; scalar_t__ scan_begin_src; int scan_begin_arg; } ;
struct TYPE_2__ {scalar_t__ main_iobase; } ;

/* Variables and functions */
 int CR_INVERT ; 
 scalar_t__ DAC_CONTROL0_REG ; 
 unsigned int DAC_ENABLE_BIT ; 
 unsigned int DAC_EXT_UPDATE_ENABLE_BIT ; 
 unsigned int DAC_EXT_UPDATE_FALLING_BIT ; 
 scalar_t__ TRIG_EXT ; 
 unsigned int WAVEFORM_GATE_ENABLE_BIT ; 
 unsigned int WAVEFORM_GATE_LEVEL_BIT ; 
 unsigned int WAVEFORM_GATE_SELECT_BIT ; 
 unsigned int WAVEFORM_TRIG_EXT_BITS ; 
 unsigned int WAVEFORM_TRIG_FALLING_BIT ; 
 unsigned int WAVEFORM_TRIG_SOFT_BITS ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static void set_dac_control0_reg(struct comedi_device *dev,
				 const struct comedi_cmd *cmd)
{
	unsigned int bits = DAC_ENABLE_BIT | WAVEFORM_GATE_LEVEL_BIT |
	    WAVEFORM_GATE_ENABLE_BIT | WAVEFORM_GATE_SELECT_BIT;

	if (cmd->start_src == TRIG_EXT) {
		bits |= WAVEFORM_TRIG_EXT_BITS;
		if (cmd->start_arg & CR_INVERT)
			bits |= WAVEFORM_TRIG_FALLING_BIT;
	} else {
		bits |= WAVEFORM_TRIG_SOFT_BITS;
	}
	if (cmd->scan_begin_src == TRIG_EXT) {
		bits |= DAC_EXT_UPDATE_ENABLE_BIT;
		if (cmd->scan_begin_arg & CR_INVERT)
			bits |= DAC_EXT_UPDATE_FALLING_BIT;
	}
	writew(bits, priv(dev)->main_iobase + DAC_CONTROL0_REG);
}
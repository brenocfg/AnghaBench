#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_ADC_Config_Data_High_Word_67xx ; 
 int /*<<< orphan*/  CAL_ADC_Config_Data_Low_Word_67xx ; 
 unsigned int CSCMD_COMMAND ; 
 unsigned int CSCMD_REGISTER_SELECT_MASK ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  cs5529_command (struct comedi_device*,unsigned int) ; 
 scalar_t__ cs5529_wait_for_idle (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_ao_win_outw (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs5529_config_write(struct comedi_device *dev, unsigned int value,
				unsigned int reg_select_bits)
{
	ni_ao_win_outw(dev, ((value >> 16) & 0xff),
		       CAL_ADC_Config_Data_High_Word_67xx);
	ni_ao_win_outw(dev, (value & 0xffff),
		       CAL_ADC_Config_Data_Low_Word_67xx);
	reg_select_bits &= CSCMD_REGISTER_SELECT_MASK;
	cs5529_command(dev, CSCMD_COMMAND | reg_select_bits);
	if (cs5529_wait_for_idle(dev))
		comedi_error(dev, "time or signal in cs5529_config_write()");
}
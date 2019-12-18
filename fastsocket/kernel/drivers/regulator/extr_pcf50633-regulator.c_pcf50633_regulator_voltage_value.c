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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum pcf50633_regulator_id { ____Placeholder_pcf50633_regulator_id } pcf50633_regulator_id ;

/* Variables and functions */
 int EINVAL ; 
#define  PCF50633_REGULATOR_AUTO 137 
#define  PCF50633_REGULATOR_DOWN1 136 
#define  PCF50633_REGULATOR_DOWN2 135 
#define  PCF50633_REGULATOR_HCLDO 134 
#define  PCF50633_REGULATOR_LDO1 133 
#define  PCF50633_REGULATOR_LDO2 132 
#define  PCF50633_REGULATOR_LDO3 131 
#define  PCF50633_REGULATOR_LDO4 130 
#define  PCF50633_REGULATOR_LDO5 129 
#define  PCF50633_REGULATOR_LDO6 128 
 int auto_voltage_value (int /*<<< orphan*/ ) ; 
 int down_voltage_value (int /*<<< orphan*/ ) ; 
 int ldo_voltage_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf50633_regulator_voltage_value(enum pcf50633_regulator_id id,
						u8 bits)
{
	int millivolts;

	switch (id) {
	case PCF50633_REGULATOR_AUTO:
		millivolts = auto_voltage_value(bits);
		break;
	case PCF50633_REGULATOR_DOWN1:
		millivolts = down_voltage_value(bits);
		break;
	case PCF50633_REGULATOR_DOWN2:
		millivolts = down_voltage_value(bits);
		break;
	case PCF50633_REGULATOR_LDO1:
	case PCF50633_REGULATOR_LDO2:
	case PCF50633_REGULATOR_LDO3:
	case PCF50633_REGULATOR_LDO4:
	case PCF50633_REGULATOR_LDO5:
	case PCF50633_REGULATOR_LDO6:
	case PCF50633_REGULATOR_HCLDO:
		millivolts = ldo_voltage_value(bits);
		break;
	default:
		return -EINVAL;
	}

	return millivolts * 1000;
}
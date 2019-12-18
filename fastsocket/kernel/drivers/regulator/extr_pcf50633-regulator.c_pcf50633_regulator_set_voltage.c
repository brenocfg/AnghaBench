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
struct regulator_dev {int dummy; } ;
struct pcf50633 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PCF50633_NUM_REGULATORS ; 
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
 int /*<<< orphan*/  auto_voltage_bits (int) ; 
 int /*<<< orphan*/  down_voltage_bits (int) ; 
 int /*<<< orphan*/  ldo_voltage_bits (int) ; 
 int pcf50633_reg_write (struct pcf50633*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcf50633_regulator_registers ; 
 struct pcf50633* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int pcf50633_regulator_set_voltage(struct regulator_dev *rdev,
						int min_uV, int max_uV)
{
	struct pcf50633 *pcf;
	int regulator_id, millivolts;
	u8 volt_bits, regnr;

	pcf = rdev_get_drvdata(rdev);

	regulator_id = rdev_get_id(rdev);
	if (regulator_id >= PCF50633_NUM_REGULATORS)
		return -EINVAL;

	millivolts = min_uV / 1000;

	regnr = pcf50633_regulator_registers[regulator_id];

	switch (regulator_id) {
	case PCF50633_REGULATOR_AUTO:
		volt_bits = auto_voltage_bits(millivolts);
		break;
	case PCF50633_REGULATOR_DOWN1:
		volt_bits = down_voltage_bits(millivolts);
		break;
	case PCF50633_REGULATOR_DOWN2:
		volt_bits = down_voltage_bits(millivolts);
		break;
	case PCF50633_REGULATOR_LDO1:
	case PCF50633_REGULATOR_LDO2:
	case PCF50633_REGULATOR_LDO3:
	case PCF50633_REGULATOR_LDO4:
	case PCF50633_REGULATOR_LDO5:
	case PCF50633_REGULATOR_LDO6:
	case PCF50633_REGULATOR_HCLDO:
		volt_bits = ldo_voltage_bits(millivolts);
		break;
	default:
		return -EINVAL;
	}

	return pcf50633_reg_write(pcf, regnr, volt_bits);
}
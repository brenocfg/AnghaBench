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
 int /*<<< orphan*/  pcf50633_reg_read (struct pcf50633*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcf50633_regulator_registers ; 
 int pcf50633_regulator_voltage_value (int,int /*<<< orphan*/ ) ; 
 struct pcf50633* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int pcf50633_regulator_get_voltage(struct regulator_dev *rdev)
{
	struct pcf50633 *pcf;
	int regulator_id;
	u8 volt_bits, regnr;

	pcf = rdev_get_drvdata(rdev);

	regulator_id = rdev_get_id(rdev);
	if (regulator_id >= PCF50633_NUM_REGULATORS)
		return -EINVAL;

	regnr = pcf50633_regulator_registers[regulator_id];

	volt_bits = pcf50633_reg_read(pcf, regnr);

	return pcf50633_regulator_voltage_value(regulator_id, volt_bits);
}
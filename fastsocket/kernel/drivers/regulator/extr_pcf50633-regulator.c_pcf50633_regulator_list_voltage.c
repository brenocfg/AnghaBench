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
struct regulator_dev {int dummy; } ;
struct pcf50633 {int dummy; } ;

/* Variables and functions */
#define  PCF50633_REGULATOR_AUTO 129 
#define  PCF50633_REGULATOR_HCLDO 128 
 int pcf50633_regulator_voltage_value (int,unsigned int) ; 
 struct pcf50633* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int pcf50633_regulator_list_voltage(struct regulator_dev *rdev,
						unsigned int index)
{
	struct pcf50633 *pcf;
	int regulator_id;

	pcf = rdev_get_drvdata(rdev);

	regulator_id = rdev_get_id(rdev);

	switch (regulator_id) {
	case PCF50633_REGULATOR_AUTO:
		index += 0x2f;
		break;
	case PCF50633_REGULATOR_HCLDO:
		index += 0x01;
		break;
	default:
		break;
	}

	return pcf50633_regulator_voltage_value(regulator_id, index);
}
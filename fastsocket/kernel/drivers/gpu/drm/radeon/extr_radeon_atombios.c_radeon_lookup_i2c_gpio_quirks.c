#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct radeon_device {scalar_t__ family; } ;
struct TYPE_4__ {int ucAccess; } ;
struct TYPE_5__ {int ucClkMaskShift; int ucDataMaskShift; int ucDataEnShift; int ucDataY_Shift; int ucDataA_Shift; TYPE_1__ sucI2cId; int /*<<< orphan*/  usClkMaskRegisterIndex; } ;
typedef  TYPE_2__ ATOM_GPIO_I2C_ASSIGMENT ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE3 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 scalar_t__ CHIP_R420 ; 
 scalar_t__ CHIP_R423 ; 
 scalar_t__ CHIP_RV410 ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_lookup_i2c_gpio_quirks(struct radeon_device *rdev,
					  ATOM_GPIO_I2C_ASSIGMENT *gpio,
					  u8 index)
{
	/* r4xx mask is technically not used by the hw, so patch in the legacy mask bits */
	if ((rdev->family == CHIP_R420) ||
	    (rdev->family == CHIP_R423) ||
	    (rdev->family == CHIP_RV410)) {
		if ((le16_to_cpu(gpio->usClkMaskRegisterIndex) == 0x0018) ||
		    (le16_to_cpu(gpio->usClkMaskRegisterIndex) == 0x0019) ||
		    (le16_to_cpu(gpio->usClkMaskRegisterIndex) == 0x001a)) {
			gpio->ucClkMaskShift = 0x19;
			gpio->ucDataMaskShift = 0x18;
		}
	}

	/* some evergreen boards have bad data for this entry */
	if (ASIC_IS_DCE4(rdev)) {
		if ((index == 7) &&
		    (le16_to_cpu(gpio->usClkMaskRegisterIndex) == 0x1936) &&
		    (gpio->sucI2cId.ucAccess == 0)) {
			gpio->sucI2cId.ucAccess = 0x97;
			gpio->ucDataMaskShift = 8;
			gpio->ucDataEnShift = 8;
			gpio->ucDataY_Shift = 8;
			gpio->ucDataA_Shift = 8;
		}
	}

	/* some DCE3 boards have bad data for this entry */
	if (ASIC_IS_DCE3(rdev)) {
		if ((index == 4) &&
		    (le16_to_cpu(gpio->usClkMaskRegisterIndex) == 0x1fda) &&
		    (gpio->sucI2cId.ucAccess == 0x94))
			gpio->sucI2cId.ucAccess = 0x14;
	}
}
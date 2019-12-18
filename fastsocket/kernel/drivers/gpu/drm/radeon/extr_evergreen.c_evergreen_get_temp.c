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
typedef  int u32 ;
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 int ASIC_T_MASK ; 
 int ASIC_T_SHIFT ; 
 int /*<<< orphan*/  CG_MULT_THERMAL_STATUS ; 
 int /*<<< orphan*/  CG_THERMAL_CTRL ; 
 int /*<<< orphan*/  CG_TS0_STATUS ; 
 scalar_t__ CHIP_JUNIPER ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int TOFFSET_MASK ; 
 int TOFFSET_SHIFT ; 
 int TS0_ADC_DOUT_MASK ; 
 int TS0_ADC_DOUT_SHIFT ; 

int evergreen_get_temp(struct radeon_device *rdev)
{
	u32 temp, toffset;
	int actual_temp = 0;

	if (rdev->family == CHIP_JUNIPER) {
		toffset = (RREG32(CG_THERMAL_CTRL) & TOFFSET_MASK) >>
			TOFFSET_SHIFT;
		temp = (RREG32(CG_TS0_STATUS) & TS0_ADC_DOUT_MASK) >>
			TS0_ADC_DOUT_SHIFT;

		if (toffset & 0x100)
			actual_temp = temp / 2 - (0x200 - toffset);
		else
			actual_temp = temp / 2 + toffset;

		actual_temp = actual_temp * 1000;

	} else {
		temp = (RREG32(CG_MULT_THERMAL_STATUS) & ASIC_T_MASK) >>
			ASIC_T_SHIFT;

		if (temp & 0x400)
			actual_temp = -256;
		else if (temp & 0x200)
			actual_temp = 255;
		else if (temp & 0x100) {
			actual_temp = temp & 0x1ff;
			actual_temp |= ~0x1ff;
		} else
			actual_temp = temp & 0xff;

		actual_temp = (actual_temp * 1000) / 2;
	}

	return actual_temp;
}
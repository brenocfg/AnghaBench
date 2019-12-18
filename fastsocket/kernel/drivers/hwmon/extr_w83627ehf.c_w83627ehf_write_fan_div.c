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
typedef  int u8 ;
struct w83627ehf_data {int* fan_div; int has_fan; } ;

/* Variables and functions */
 int /*<<< orphan*/  W83627EHF_REG_DIODE ; 
 int /*<<< orphan*/  W83627EHF_REG_FANDIV1 ; 
 int /*<<< orphan*/  W83627EHF_REG_FANDIV2 ; 
 int /*<<< orphan*/  W83627EHF_REG_SMI_OVT ; 
 int /*<<< orphan*/  W83627EHF_REG_VBAT ; 
 int w83627ehf_read_value (struct w83627ehf_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627ehf_write_value (struct w83627ehf_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void w83627ehf_write_fan_div(struct w83627ehf_data *data, int nr)
{
	u8 reg;

	switch (nr) {
	case 0:
		reg = (w83627ehf_read_value(data, W83627EHF_REG_FANDIV1) & 0xcf)
		    | ((data->fan_div[0] & 0x03) << 4);
		/* fan5 input control bit is write only, compute the value */
		reg |= (data->has_fan & (1 << 4)) ? 1 : 0;
		w83627ehf_write_value(data, W83627EHF_REG_FANDIV1, reg);
		reg = (w83627ehf_read_value(data, W83627EHF_REG_VBAT) & 0xdf)
		    | ((data->fan_div[0] & 0x04) << 3);
		w83627ehf_write_value(data, W83627EHF_REG_VBAT, reg);
		break;
	case 1:
		reg = (w83627ehf_read_value(data, W83627EHF_REG_FANDIV1) & 0x3f)
		    | ((data->fan_div[1] & 0x03) << 6);
		/* fan5 input control bit is write only, compute the value */
		reg |= (data->has_fan & (1 << 4)) ? 1 : 0;
		w83627ehf_write_value(data, W83627EHF_REG_FANDIV1, reg);
		reg = (w83627ehf_read_value(data, W83627EHF_REG_VBAT) & 0xbf)
		    | ((data->fan_div[1] & 0x04) << 4);
		w83627ehf_write_value(data, W83627EHF_REG_VBAT, reg);
		break;
	case 2:
		reg = (w83627ehf_read_value(data, W83627EHF_REG_FANDIV2) & 0x3f)
		    | ((data->fan_div[2] & 0x03) << 6);
		w83627ehf_write_value(data, W83627EHF_REG_FANDIV2, reg);
		reg = (w83627ehf_read_value(data, W83627EHF_REG_VBAT) & 0x7f)
		    | ((data->fan_div[2] & 0x04) << 5);
		w83627ehf_write_value(data, W83627EHF_REG_VBAT, reg);
		break;
	case 3:
		reg = (w83627ehf_read_value(data, W83627EHF_REG_DIODE) & 0xfc)
		    | (data->fan_div[3] & 0x03);
		w83627ehf_write_value(data, W83627EHF_REG_DIODE, reg);
		reg = (w83627ehf_read_value(data, W83627EHF_REG_SMI_OVT) & 0x7f)
		    | ((data->fan_div[3] & 0x04) << 5);
		w83627ehf_write_value(data, W83627EHF_REG_SMI_OVT, reg);
		break;
	case 4:
		reg = (w83627ehf_read_value(data, W83627EHF_REG_DIODE) & 0x73)
		    | ((data->fan_div[4] & 0x03) << 2)
		    | ((data->fan_div[4] & 0x04) << 5);
		w83627ehf_write_value(data, W83627EHF_REG_DIODE, reg);
		break;
	}
}
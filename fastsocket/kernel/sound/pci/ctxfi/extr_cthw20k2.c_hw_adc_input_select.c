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
struct hw {int dummy; } ;
typedef  enum ADCSRC { ____Placeholder_ADCSRC } ADCSRC ;

/* Variables and functions */
#define  ADC_LINEIN 129 
#define  ADC_MICIN 128 
 int /*<<< orphan*/  GPIO_DATA ; 
 int /*<<< orphan*/  MAKE_WM8775_ADDR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAKE_WM8775_DATA (int) ; 
 int /*<<< orphan*/  WM8775_AADCL ; 
 int /*<<< orphan*/  WM8775_AADCR ; 
 int /*<<< orphan*/  WM8775_ADCMC ; 
 int /*<<< orphan*/  hw20k2_i2c_write (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hw_adc_input_select(struct hw *hw, enum ADCSRC type)
{
	u32 data;

	data = hw_read_20kx(hw, GPIO_DATA);
	switch (type) {
	case ADC_MICIN:
		data |= (0x1 << 14);
		hw_write_20kx(hw, GPIO_DATA, data);
		hw20k2_i2c_write(hw, MAKE_WM8775_ADDR(WM8775_ADCMC, 0x101),
				MAKE_WM8775_DATA(0x101)); /* Mic-in */
		hw20k2_i2c_write(hw, MAKE_WM8775_ADDR(WM8775_AADCL, 0xE7),
				MAKE_WM8775_DATA(0xE7)); /* +12dB boost */
		hw20k2_i2c_write(hw, MAKE_WM8775_ADDR(WM8775_AADCR, 0xE7),
				MAKE_WM8775_DATA(0xE7)); /* +12dB boost */
		break;
	case ADC_LINEIN:
		data &= ~(0x1 << 14);
		hw_write_20kx(hw, GPIO_DATA, data);
		hw20k2_i2c_write(hw, MAKE_WM8775_ADDR(WM8775_ADCMC, 0x102),
				MAKE_WM8775_DATA(0x102)); /* Line-in */
		hw20k2_i2c_write(hw, MAKE_WM8775_ADDR(WM8775_AADCL, 0xCF),
				MAKE_WM8775_DATA(0xCF)); /* No boost */
		hw20k2_i2c_write(hw, MAKE_WM8775_ADDR(WM8775_AADCR, 0xCF),
				MAKE_WM8775_DATA(0xCF)); /* No boost */
		break;
	default:
		break;
	}

	return 0;
}
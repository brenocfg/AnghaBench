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
#define  ADC_LINEIN 130 
#define  ADC_MICIN 129 
#define  ADC_NONE 128 
 int /*<<< orphan*/  GPIO ; 
 int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 unsigned int hw_read_pci (struct hw*,int) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_write_pci (struct hw*,int,int) ; 
 int /*<<< orphan*/  i2c_lock (struct hw*) ; 
 scalar_t__ i2c_unlock (struct hw*) ; 
 int /*<<< orphan*/  i2c_write (struct hw*,int,int,int) ; 

__attribute__((used)) static int
adc_input_select_SBx(struct hw *hw, enum ADCSRC type, unsigned char boost)
{
	u32 data;
	u32 i2c_data;
	unsigned int ret;

	if (i2c_unlock(hw))
		return -1;

	do {
		ret = hw_read_pci(hw, 0xEC);
	} while (!(ret & 0x800000)); /* i2c ready poll */
	/* set i2c access mode as Direct Control */
	hw_write_pci(hw, 0xEC, 0x05);

	data = hw_read_20kx(hw, GPIO);
	switch (type) {
	case ADC_MICIN:
		data |= ((0x1 << 7) | (0x1 << 8));
		i2c_data = 0x1;  /* Mic-in */
		break;
	case ADC_LINEIN:
		data &= ~(0x1 << 7);
		data |= (0x1 << 8);
		i2c_data = 0x2; /* Line-in */
		break;
	case ADC_NONE:
		data &= ~(0x1 << 8);
		i2c_data = 0x0; /* set to Digital */
		break;
	default:
		i2c_lock(hw);
		return -1;
	}
	hw_write_20kx(hw, GPIO, data);
	i2c_write(hw, 0x001a0080, 0x2a, i2c_data);
	if (boost) {
		i2c_write(hw, 0x001a0080, 0x1c, 0xe7); /* +12dB boost */
		i2c_write(hw, 0x001a0080, 0x1e, 0xe7); /* +12dB boost */
	} else {
		i2c_write(hw, 0x001a0080, 0x1c, 0xcf); /* No boost */
		i2c_write(hw, 0x001a0080, 0x1e, 0xcf); /* No boost */
	}

	i2c_lock(hw);

	return 0;
}
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
 int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_is_adc_input_selected(struct hw *hw, enum ADCSRC type)
{
	u32 data;

	data = hw_read_20kx(hw, GPIO_DATA);
	switch (type) {
	case ADC_MICIN:
		data = (data & (0x1 << 14)) ? 1 : 0;
		break;
	case ADC_LINEIN:
		data = (data & (0x1 << 14)) ? 0 : 1;
		break;
	default:
		data = 0;
	}
	return data;
}
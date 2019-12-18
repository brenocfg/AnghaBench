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

__attribute__((used)) static int is_adc_input_selected_SBx(struct hw *hw, enum ADCSRC type)
{
	u32 data;

	data = hw_read_20kx(hw, GPIO);
	switch (type) {
	case ADC_MICIN:
		data = ((data & (0x1<<7)) && (data & (0x1<<8)));
		break;
	case ADC_LINEIN:
		data = (!(data & (0x1<<7)) && (data & (0x1<<8)));
		break;
	case ADC_NONE: /* Digital I/O */
		data = (!(data & (0x1<<8)));
		break;
	default:
		data = 0;
	}
	return data;
}
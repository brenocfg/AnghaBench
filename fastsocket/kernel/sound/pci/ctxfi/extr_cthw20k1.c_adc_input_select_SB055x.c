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
#define  ADC_AUX 131 
#define  ADC_LINEIN 130 
#define  ADC_MICIN 129 
#define  ADC_NONE 128 
 int /*<<< orphan*/  GPIO ; 
 int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
adc_input_select_SB055x(struct hw *hw, enum ADCSRC type, unsigned char boost)
{
	u32 data;

	/*
	 * check and set the following GPIO bits accordingly
	 * ADC_Gain		= GPIO2
	 * DRM_off		= GPIO3
	 * Mic_Pwr_on		= GPIO7
	 * Digital_IO_Sel	= GPIO8
	 * Mic_Sw		= GPIO9
	 * Aux/MicLine_Sw	= GPIO12
	 */
	data = hw_read_20kx(hw, GPIO);
	data &= 0xec73;
	switch (type) {
	case ADC_MICIN:
		data |= (0x1<<7) | (0x1<<8) | (0x1<<9) ;
		data |= boost ? (0x1<<2) : 0;
		break;
	case ADC_LINEIN:
		data |= (0x1<<8);
		break;
	case ADC_AUX:
		data |= (0x1<<8) | (0x1<<12);
		break;
	case ADC_NONE:
		data |= (0x1<<12);  /* set to digital */
		break;
	default:
		return -1;
	}

	hw_write_20kx(hw, GPIO, data);

	return 0;
}
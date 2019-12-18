#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int bit_width; scalar_t__ atten; int /*<<< orphan*/  coeff_b; int /*<<< orphan*/  coeff_a; int /*<<< orphan*/  high_curve; int /*<<< orphan*/  low_curve; int /*<<< orphan*/  vref; } ;
typedef  TYPE_1__ esp_adc_cal_characteristics_t ;

/* Variables and functions */
 int ADC_12_BIT_RES ; 
 scalar_t__ ADC_ATTEN_DB_11 ; 
 int ADC_WIDTH_BIT_12 ; 
 int /*<<< orphan*/  LUT_ADC_STEP_SIZE ; 
 scalar_t__ LUT_ENABLED ; 
 int LUT_HIGH_THRESH ; 
 int LUT_LOW_THRESH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int calculate_voltage_linear (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int calculate_voltage_lut (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int interpolate_two_points (int,int,int /*<<< orphan*/ ,int) ; 

uint32_t esp_adc_cal_raw_to_voltage(uint32_t adc_reading, const esp_adc_cal_characteristics_t *chars)
{
    assert(chars != NULL);

    //Scale adc_rading if not 12 bits wide
    adc_reading = (adc_reading << (ADC_WIDTH_BIT_12 - chars->bit_width));
    if (adc_reading > ADC_12_BIT_RES - 1) {
        adc_reading = ADC_12_BIT_RES - 1;    //Set to 12bit res max
    }

    if (LUT_ENABLED && (chars->atten == ADC_ATTEN_DB_11) && (adc_reading >= LUT_LOW_THRESH)) {  //Check if in non-linear region
        //Use lookup table to get voltage in non linear portion of ADC_ATTEN_DB_11
        uint32_t lut_voltage = calculate_voltage_lut(adc_reading, chars->vref, chars->low_curve, chars->high_curve);
        if (adc_reading <= LUT_HIGH_THRESH) {   //If ADC is transitioning from linear region to non-linear region
            //Linearly interpolate between linear voltage and lut voltage
            uint32_t linear_voltage = calculate_voltage_linear(adc_reading, chars->coeff_a, chars->coeff_b);
            return interpolate_two_points(linear_voltage, lut_voltage, LUT_ADC_STEP_SIZE, (adc_reading - LUT_LOW_THRESH));
        } else {
            return lut_voltage;
        }
    } else {
        return calculate_voltage_linear(adc_reading, chars->coeff_a, chars->coeff_b);
    }
}
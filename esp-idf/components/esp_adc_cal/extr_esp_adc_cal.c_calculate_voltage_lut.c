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
typedef  int uint32_t ;

/* Variables and functions */
 int LUT_ADC_STEP_SIZE ; 
 int LUT_LOW_THRESH ; 
 int LUT_VREF_HIGH ; 
 int LUT_VREF_LOW ; 

__attribute__((used)) static uint32_t calculate_voltage_lut(uint32_t adc, uint32_t vref, const uint32_t *low_vref_curve, const uint32_t *high_vref_curve)
{
    //Get index of lower bound points of LUT
    uint32_t i = (adc - LUT_LOW_THRESH) / LUT_ADC_STEP_SIZE;

    //Let the X Axis be Vref, Y axis be ADC reading, and Z be voltage
    int x2dist = LUT_VREF_HIGH - vref;                 //(x2 - x)
    int x1dist = vref - LUT_VREF_LOW;                  //(x - x1)
    int y2dist = ((i + 1) * LUT_ADC_STEP_SIZE) + LUT_LOW_THRESH - adc;  //(y2 - y)
    int y1dist = adc - ((i * LUT_ADC_STEP_SIZE) + LUT_LOW_THRESH);        //(y - y1)

    //For points for bilinear interpolation
    int q11 = low_vref_curve[i];                    //Lower bound point of low_vref_curve
    int q12 = low_vref_curve[i + 1];                //Upper bound point of low_vref_curve
    int q21 = high_vref_curve[i];                   //Lower bound point of high_vref_curve
    int q22 = high_vref_curve[i + 1];               //Upper bound point of high_vref_curve

    //Bilinear interpolation
    //Where z = 1/((x2-x1)*(y2-y1)) * ( (q11*x2dist*y2dist) + (q21*x1dist*y2dist) + (q12*x2dist*y1dist) + (q22*x1dist*y1dist) )
    int voltage = (q11 * x2dist * y2dist) + (q21 * x1dist * y2dist) + (q12 * x2dist * y1dist) + (q22 * x1dist * y1dist);
    voltage += ((LUT_VREF_HIGH - LUT_VREF_LOW) * LUT_ADC_STEP_SIZE) / 2; //Integer division rounding
    voltage /= ((LUT_VREF_HIGH - LUT_VREF_LOW) * LUT_ADC_STEP_SIZE);    //Divide by ((x2-x1)*(y2-y1))
    return (uint32_t)voltage;
}
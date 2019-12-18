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
 int LIN_COEFF_A_ROUND ; 
 int LIN_COEFF_A_SCALE ; 

__attribute__((used)) static uint32_t calculate_voltage_linear(uint32_t adc_reading, uint32_t coeff_a, uint32_t coeff_b)
{
    //Where voltage = coeff_a * adc_reading + coeff_b
    return (((coeff_a * adc_reading) + LIN_COEFF_A_ROUND) / LIN_COEFF_A_SCALE) + coeff_b;
}
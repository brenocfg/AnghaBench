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
typedef  scalar_t__ adc_unit_t ;

/* Variables and functions */
 scalar_t__ ADC_UNIT_1 ; 
 int /*<<< orphan*/  EFUSE_RD_ADC1_TP_LOW ; 
 int /*<<< orphan*/  EFUSE_RD_ADC2_TP_LOW ; 
 int REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TP_LOW1_OFFSET ; 
 int TP_LOW2_OFFSET ; 
 int /*<<< orphan*/  TP_LOW_MASK ; 
 int /*<<< orphan*/  TP_REG ; 
 int TP_STEP_SIZE ; 
 int decode_bits (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t read_efuse_tp_low(adc_unit_t adc_num)
{
    //ADC reading at 150mV stored in two's complement format
    uint32_t ret;
    uint32_t bits;

    if (adc_num == ADC_UNIT_1) {
        ret = TP_LOW1_OFFSET;
        bits = REG_GET_FIELD(TP_REG, EFUSE_RD_ADC1_TP_LOW);
    } else {
        ret = TP_LOW2_OFFSET;
        bits = REG_GET_FIELD(TP_REG, EFUSE_RD_ADC2_TP_LOW);
    }
    ret += decode_bits(bits, TP_LOW_MASK, true) * TP_STEP_SIZE;
    return ret;     //Reading of ADC at 150mV
}
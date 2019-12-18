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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  SENS_SAR1_BIT_WIDTH ; 
 int /*<<< orphan*/  SENS_SAR1_BIT_WIDTH_S ; 
 int /*<<< orphan*/  SENS_SAR1_SAMPLE_BIT ; 
 int /*<<< orphan*/  SENS_SAR1_SAMPLE_BIT_S ; 
 int /*<<< orphan*/  SENS_SAR2_BIT_WIDTH ; 
 int /*<<< orphan*/  SENS_SAR2_BIT_WIDTH_S ; 
 int /*<<< orphan*/  SENS_SAR2_SAMPLE_BIT ; 
 int /*<<< orphan*/  SENS_SAR2_SAMPLE_BIT_S ; 
 int /*<<< orphan*/  SENS_SAR_READ_CTRL2_REG ; 
 int /*<<< orphan*/  SENS_SAR_READ_CTRL_REG ; 
 int /*<<< orphan*/  SENS_SAR_START_FORCE_REG ; 
 int /*<<< orphan*/  SET_PERI_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int __analogReturnedWidth ; 
 int __analogWidth ; 

void __analogSetWidth(uint8_t bits){
    if(bits < 9){
        bits = 9;
    } else if(bits > 12){
        bits = 12;
    }
    __analogReturnedWidth = bits;
    __analogWidth = bits - 9;
    SET_PERI_REG_BITS(SENS_SAR_START_FORCE_REG, SENS_SAR1_BIT_WIDTH, __analogWidth, SENS_SAR1_BIT_WIDTH_S);
    SET_PERI_REG_BITS(SENS_SAR_READ_CTRL_REG, SENS_SAR1_SAMPLE_BIT, __analogWidth, SENS_SAR1_SAMPLE_BIT_S);

    SET_PERI_REG_BITS(SENS_SAR_START_FORCE_REG, SENS_SAR2_BIT_WIDTH, __analogWidth, SENS_SAR2_BIT_WIDTH_S);
    SET_PERI_REG_BITS(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_SAMPLE_BIT, __analogWidth, SENS_SAR2_SAMPLE_BIT_S);
}
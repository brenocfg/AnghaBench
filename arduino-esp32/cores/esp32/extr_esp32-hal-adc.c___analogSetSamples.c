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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  SENS_SAR1_SAMPLE_NUM ; 
 int /*<<< orphan*/  SENS_SAR1_SAMPLE_NUM_S ; 
 int /*<<< orphan*/  SENS_SAR2_SAMPLE_NUM ; 
 int /*<<< orphan*/  SENS_SAR2_SAMPLE_NUM_S ; 
 int /*<<< orphan*/  SENS_SAR_READ_CTRL2_REG ; 
 int /*<<< orphan*/  SENS_SAR_READ_CTRL_REG ; 
 int /*<<< orphan*/  SET_PERI_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ __analogSamples ; 

void __analogSetSamples(uint8_t samples){
    if(!samples){
        return;
    }
    __analogSamples = samples - 1;
    SET_PERI_REG_BITS(SENS_SAR_READ_CTRL_REG, SENS_SAR1_SAMPLE_NUM, __analogSamples, SENS_SAR1_SAMPLE_NUM_S);
    SET_PERI_REG_BITS(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_SAMPLE_NUM, __analogSamples, SENS_SAR2_SAMPLE_NUM_S);
}
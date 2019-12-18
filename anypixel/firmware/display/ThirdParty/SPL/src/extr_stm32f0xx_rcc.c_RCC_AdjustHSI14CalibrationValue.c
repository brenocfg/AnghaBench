#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int CR2; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RCC_HSI14_CALIBRATION_VALUE (scalar_t__) ; 
 TYPE_1__* RCC ; 
 int RCC_CR2_HSI14TRIM ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_AdjustHSI14CalibrationValue(uint8_t HSI14CalibrationValue)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_HSI14_CALIBRATION_VALUE(HSI14CalibrationValue));
  
  tmpreg = RCC->CR2;
  
  /* Clear HSI14TRIM[4:0] bits */
  tmpreg &= ~RCC_CR2_HSI14TRIM;
  
  /* Set the HSITRIM14[4:0] bits according to HSI14CalibrationValue value */
  tmpreg |= (uint32_t)HSI14CalibrationValue << 3;

  /* Store the new value */
  RCC->CR2 = tmpreg;
}
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
typedef  int /*<<< orphan*/  TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  IS_TIM_ALL_PERIPH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCC_APB1PeriphResetCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB1Periph_TIM14 ; 
 int /*<<< orphan*/  RCC_APB1Periph_TIM2 ; 
 int /*<<< orphan*/  RCC_APB1Periph_TIM3 ; 
 int /*<<< orphan*/  RCC_APB1Periph_TIM6 ; 
 int /*<<< orphan*/  RCC_APB1Periph_TIM7 ; 
 int /*<<< orphan*/  RCC_APB2PeriphResetCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB2Periph_TIM1 ; 
 int /*<<< orphan*/  RCC_APB2Periph_TIM15 ; 
 int /*<<< orphan*/  RCC_APB2Periph_TIM16 ; 
 int /*<<< orphan*/  RCC_APB2Periph_TIM17 ; 
 int /*<<< orphan*/ * TIM1 ; 
 int /*<<< orphan*/ * TIM14 ; 
 int /*<<< orphan*/ * TIM15 ; 
 int /*<<< orphan*/ * TIM16 ; 
 int /*<<< orphan*/ * TIM17 ; 
 int /*<<< orphan*/ * TIM2 ; 
 int /*<<< orphan*/ * TIM3 ; 
 int /*<<< orphan*/ * TIM6 ; 
 int /*<<< orphan*/ * TIM7 ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_DeInit(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx)); 

  if (TIMx == TIM1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);  
  }     
  else if (TIMx == TIM2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
  }
  else if (TIMx == TIM3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, DISABLE);
  }
  else if (TIMx == TIM6)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
  } 
  else if (TIMx == TIM7)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, DISABLE);
  }
  else if (TIMx == TIM14) 
  {       
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, DISABLE);  
  }        
  else if (TIMx == TIM15)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM15, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM15, DISABLE);
  } 
  else if (TIMx == TIM16)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, DISABLE);
  } 
  else
  {
    if (TIMx == TIM17)
    {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM17, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM17, DISABLE);
    }  
  }
     
}
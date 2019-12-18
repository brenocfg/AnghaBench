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
typedef  int /*<<< orphan*/  GPIO_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/ * GPIOA ; 
 int /*<<< orphan*/ * GPIOB ; 
 int /*<<< orphan*/ * GPIOC ; 
 int /*<<< orphan*/ * GPIOD ; 
 int /*<<< orphan*/ * GPIOE ; 
 int /*<<< orphan*/ * GPIOF ; 
 int /*<<< orphan*/  IS_GPIO_ALL_PERIPH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCC_AHBPeriphResetCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_AHBPeriph_GPIOA ; 
 int /*<<< orphan*/  RCC_AHBPeriph_GPIOB ; 
 int /*<<< orphan*/  RCC_AHBPeriph_GPIOC ; 
 int /*<<< orphan*/  RCC_AHBPeriph_GPIOD ; 
 int /*<<< orphan*/  RCC_AHBPeriph_GPIOE ; 
 int /*<<< orphan*/  RCC_AHBPeriph_GPIOF ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  if(GPIOx == GPIOA)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, DISABLE);
  }
  else if(GPIOx == GPIOB)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, DISABLE);
  }
  else if(GPIOx == GPIOC)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, DISABLE);
  }
  else if(GPIOx == GPIOD)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, DISABLE);
  }
  else if(GPIOx == GPIOE)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOE, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOE, DISABLE);
  }
  else
  {
    if(GPIOx == GPIOF)
    {
      RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, ENABLE);
      RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, DISABLE);
    }
  }
}
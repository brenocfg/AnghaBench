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
 int /*<<< orphan*/ * GPIOG ; 
 int /*<<< orphan*/ * GPIOH ; 
 int /*<<< orphan*/ * GPIOI ; 
 int /*<<< orphan*/  IS_GPIO_ALL_PERIPH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCC_AHB1PeriphResetCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_AHB1Periph_GPIOA ; 
 int /*<<< orphan*/  RCC_AHB1Periph_GPIOB ; 
 int /*<<< orphan*/  RCC_AHB1Periph_GPIOC ; 
 int /*<<< orphan*/  RCC_AHB1Periph_GPIOD ; 
 int /*<<< orphan*/  RCC_AHB1Periph_GPIOE ; 
 int /*<<< orphan*/  RCC_AHB1Periph_GPIOF ; 
 int /*<<< orphan*/  RCC_AHB1Periph_GPIOG ; 
 int /*<<< orphan*/  RCC_AHB1Periph_GPIOH ; 
 int /*<<< orphan*/  RCC_AHB1Periph_GPIOI ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  if (GPIOx == GPIOA)
  {
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA, DISABLE);
  }
  else if (GPIOx == GPIOB)
  {
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, DISABLE);
  }
  else if (GPIOx == GPIOC)
  {
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOC, DISABLE);
  }
  else if (GPIOx == GPIOD)
  {
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD, DISABLE);
  }
  else if (GPIOx == GPIOE)
  {
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOE, DISABLE);
  }
  else if (GPIOx == GPIOF)
  {
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOF, DISABLE);
  }
  else if (GPIOx == GPIOG)
  {
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOG, DISABLE);
  }
  else if (GPIOx == GPIOH)
  {
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOH, ENABLE);
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOH, DISABLE);
  }
  else
  {
    if (GPIOx == GPIOI)
    {
      RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOI, ENABLE);
      RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOI, DISABLE);
    }
  }
}
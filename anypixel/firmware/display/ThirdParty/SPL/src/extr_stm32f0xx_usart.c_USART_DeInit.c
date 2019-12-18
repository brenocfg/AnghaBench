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
typedef  int /*<<< orphan*/  USART_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  IS_USART_ALL_PERIPH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCC_APB1PeriphResetCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB1Periph_USART2 ; 
 int /*<<< orphan*/  RCC_APB1Periph_USART3 ; 
 int /*<<< orphan*/  RCC_APB1Periph_USART4 ; 
 int /*<<< orphan*/  RCC_APB2PeriphResetCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB2Periph_USART1 ; 
 int /*<<< orphan*/ * USART1 ; 
 int /*<<< orphan*/ * USART2 ; 
 int /*<<< orphan*/ * USART3 ; 
 int /*<<< orphan*/ * USART4 ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_DeInit(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  if (USARTx == USART1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
  }
  else if (USARTx == USART2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
  }
  else if (USARTx == USART3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
  }
  else 
  {
    if  (USARTx == USART4)
    {
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART4, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART4, DISABLE);
    }
  }
}
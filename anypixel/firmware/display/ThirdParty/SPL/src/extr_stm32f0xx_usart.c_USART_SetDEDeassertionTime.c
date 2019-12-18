#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int CR1; } ;
typedef  TYPE_1__ USART_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_USART_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_USART_DE_ASSERTION_DEASSERTION_TIME (int) ; 
 scalar_t__ USART_CR1_DEDT ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_SetDEDeassertionTime(USART_TypeDef* USARTx, uint32_t USART_DEDeassertionTime)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_ASSERTION_DEASSERTION_TIME(USART_DEDeassertionTime)); 

  /* Clear the DE deassertion time */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_DEDT);
  /* Set the new value for the DE deassertion time */
  USARTx->CR1 |=((uint32_t)USART_DEDeassertionTime << (uint32_t)0x10);
}
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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ CR3; } ;
typedef  TYPE_1__ USART_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_USART_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_USART_DE_POLARITY (scalar_t__) ; 
 scalar_t__ USART_CR3_DEP ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_DEPolarityConfig(USART_TypeDef* USARTx, uint32_t USART_DEPolarity)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_POLARITY(USART_DEPolarity));

  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DEP);
  USARTx->CR3 |= USART_DEPolarity;
}
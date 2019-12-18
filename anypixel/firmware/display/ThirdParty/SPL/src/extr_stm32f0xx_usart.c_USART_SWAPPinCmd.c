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
struct TYPE_4__ {scalar_t__ CR2; } ;
typedef  TYPE_1__ USART_TypeDef ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  IS_USART_ALL_PERIPH (TYPE_1__*) ; 
 scalar_t__ USART_CR2_SWAP ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_SWAPPinCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SWAP feature by setting the SWAP bit in the CR2 register */
    USARTx->CR2 |= USART_CR2_SWAP;
  }
  else
  {
    /* Disable the SWAP feature by clearing the SWAP bit in the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_SWAP);
  }
}
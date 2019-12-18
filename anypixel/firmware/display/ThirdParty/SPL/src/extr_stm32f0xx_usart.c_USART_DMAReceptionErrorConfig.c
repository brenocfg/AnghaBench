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
 int /*<<< orphan*/  IS_USART_DMAONERROR (scalar_t__) ; 
 scalar_t__ USART_CR3_DDRE ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_DMAReceptionErrorConfig(USART_TypeDef* USARTx, uint32_t USART_DMAOnError)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DMAONERROR(USART_DMAOnError)); 
  
  /* Clear the DMA Reception error detection bit */
  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DDRE);
  /* Set the new value for the DMA Reception error detection bit */
  USARTx->CR3 |= USART_DMAOnError;
}
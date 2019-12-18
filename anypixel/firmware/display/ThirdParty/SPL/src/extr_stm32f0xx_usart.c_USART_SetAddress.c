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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int CR2; } ;
typedef  TYPE_1__ USART_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_USART_ALL_PERIPH (TYPE_1__*) ; 
 scalar_t__ USART_CR2_ADD ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* Clear the USART address */
  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ADD);
  /* Set the USART address node */
  USARTx->CR2 |=((uint32_t)USART_Address << (uint32_t)0x18);
}
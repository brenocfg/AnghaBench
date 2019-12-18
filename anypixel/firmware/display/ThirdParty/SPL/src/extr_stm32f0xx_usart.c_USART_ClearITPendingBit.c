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
struct TYPE_4__ {int ICR; } ;
typedef  TYPE_1__ USART_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_USART_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_USART_CLEAR_IT (int) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint32_t USART_IT)
{
  uint32_t bitpos = 0, itmask = 0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_IT(USART_IT)); 
  
  bitpos = USART_IT >> 0x10;
  itmask = ((uint32_t)0x01 << (uint32_t)bitpos);
  USARTx->ICR = (uint32_t)itmask;
}
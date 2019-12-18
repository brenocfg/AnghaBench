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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ CR2; } ;
typedef  TYPE_1__ USART_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_USART_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_USART_LIN_BREAK_DETECT_LENGTH (scalar_t__) ; 
 scalar_t__ USART_CR2_LBDL ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_LIN_BREAK_DETECT_LENGTH(USART_LINBreakDetectLength));
  
  USARTx->CR2 &= (uint16_t)~((uint16_t)USART_CR2_LBDL);
  USARTx->CR2 |= USART_LINBreakDetectLength;  
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int SR; } ;
typedef  TYPE_1__ USART_TypeDef ;
typedef  scalar_t__ FlagStatus ;

/* Variables and functions */
 int /*<<< orphan*/  IS_USART_1236_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_USART_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_USART_FLAG (int) ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int USART_FLAG_CTS ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_FLAG(USART_FLAG));

  /* The CTS flag is not available for UART4 and UART5 */
  if (USART_FLAG == USART_FLAG_CTS)
  {
    assert_param(IS_USART_1236_PERIPH(USARTx));
  } 
    
  if ((USARTx->SR & USART_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}
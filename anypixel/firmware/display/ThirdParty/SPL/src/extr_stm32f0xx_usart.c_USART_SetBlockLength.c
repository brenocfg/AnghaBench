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
struct TYPE_4__ {int RTOR; } ;
typedef  TYPE_1__ USART_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_USART_12_PERIPH (TYPE_1__*) ; 
 scalar_t__ USART_RTOR_BLEN ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_SetBlockLength(USART_TypeDef* USARTx, uint8_t USART_BlockLength)
{    
  /* Check the parameters */
  assert_param(IS_USART_12_PERIPH(USARTx));

  /* Clear the Smart card block length */
  USARTx->RTOR &= (uint32_t)~((uint32_t)USART_RTOR_BLEN);
  /* Set the Smart Card block length */
  USARTx->RTOR |= (uint32_t)((uint32_t)USART_BlockLength << 0x18);
}
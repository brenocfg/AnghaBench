#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int CFGR3; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RCC_USARTCLK (int) ; 
 TYPE_1__* RCC ; 
 int RCC_CFGR3_USART1SW ; 
 int RCC_CFGR3_USART2SW ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void RCC_USARTCLKConfig(uint32_t RCC_USARTCLK)
{ 
  uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_RCC_USARTCLK(RCC_USARTCLK));

  /* Get USART index */
  tmp = (RCC_USARTCLK >> 28);

  /* Clear USARTSW[1:0] bit */
  if (tmp == (uint32_t)0x00000001)
  {
    /* Clear USART1SW[1:0] bit */  
    RCC->CFGR3 &= ~RCC_CFGR3_USART1SW;
  }
  else
  {
    /* Clear USART2SW[1:0] bit */
    RCC->CFGR3 &= ~RCC_CFGR3_USART2SW;
  }

  /* Set USARTxSW bits according to RCC_USARTCLK value */
  RCC->CFGR3 |= RCC_USARTCLK;
}
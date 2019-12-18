#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ CR2; } ;
typedef  TYPE_1__ USART_TypeDef ;
struct TYPE_7__ {int USART_Clock; int USART_CPOL; int USART_CPHA; int USART_LastBit; } ;
typedef  TYPE_2__ USART_ClockInitTypeDef ;

/* Variables and functions */
 scalar_t__ CR2_CLOCK_CLEAR_MASK ; 
 int /*<<< orphan*/  IS_USART_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_USART_CLOCK (int) ; 
 int /*<<< orphan*/  IS_USART_CPHA (int) ; 
 int /*<<< orphan*/  IS_USART_CPOL (int) ; 
 int /*<<< orphan*/  IS_USART_LASTBIT (int) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
  assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
  assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));
/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear CLKEN, CPOL, CPHA, LBCL and SSM bits */
  tmpreg &= (uint32_t)~((uint32_t)CR2_CLOCK_CLEAR_MASK);
  /* Configure the USART Clock, CPOL, CPHA, LastBit and SSM ------------*/
  /* Set CLKEN bit according to USART_Clock value */
  /* Set CPOL bit according to USART_CPOL value */
  /* Set CPHA bit according to USART_CPHA value */
  /* Set LBCL bit according to USART_LastBit value */
  tmpreg |= (uint32_t)(USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL | 
                       USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit);
  /* Write to USART CR2 */
  USARTx->CR2 = tmpreg;
}
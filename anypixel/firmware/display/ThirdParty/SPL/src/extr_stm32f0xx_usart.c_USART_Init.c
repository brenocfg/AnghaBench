#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_10__ {int CR1; int CR2; int CR3; int BRR; } ;
typedef  TYPE_1__ USART_TypeDef ;
struct TYPE_11__ {int USART_BaudRate; int USART_Parity; int USART_Mode; int USART_HardwareFlowControl; scalar_t__ USART_WordLength; scalar_t__ USART_StopBits; } ;
typedef  TYPE_2__ USART_InitTypeDef ;
struct TYPE_12__ {int USART1CLK_Frequency; int USART2CLK_Frequency; int PCLK_Frequency; } ;
typedef  TYPE_3__ RCC_ClocksTypeDef ;

/* Variables and functions */
 scalar_t__ CR1_CLEAR_MASK ; 
 scalar_t__ CR3_CLEAR_MASK ; 
 int /*<<< orphan*/  IS_USART_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_USART_BAUDRATE (int) ; 
 int /*<<< orphan*/  IS_USART_HARDWARE_FLOW_CONTROL (int) ; 
 int /*<<< orphan*/  IS_USART_MODE (int) ; 
 int /*<<< orphan*/  IS_USART_PARITY (int) ; 
 int /*<<< orphan*/  IS_USART_STOPBITS (scalar_t__) ; 
 int /*<<< orphan*/  IS_USART_WORD_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  RCC_GetClocksFreq (TYPE_3__*) ; 
 TYPE_1__* USART1 ; 
 TYPE_1__* USART2 ; 
 int USART_CR1_OVER8 ; 
 scalar_t__ USART_CR1_UE ; 
 scalar_t__ USART_CR2_STOP ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  uint32_t divider = 0, apbclock = 0, tmpreg = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));  
  assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
  assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
  assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
  
  /* Disable USART */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UE);
  
  /*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear STOP[13:12] bits */
  tmpreg &= (uint32_t)~((uint32_t)USART_CR2_STOP);
  
  /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
  /* Set STOP[13:12] bits according to USART_StopBits value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;
  
  /* Write to USART CR2 */
  USARTx->CR2 = tmpreg;
  
  /*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;
  /* Clear M, PCE, PS, TE and RE bits */
  tmpreg &= (uint32_t)~((uint32_t)CR1_CLEAR_MASK);
  
  /* Configure the USART Word Length, Parity and mode ----------------------- */
  /* Set the M bits according to USART_WordLength value */
  /* Set PCE and PS bits according to USART_Parity value */
  /* Set TE and RE bits according to USART_Mode value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
    USART_InitStruct->USART_Mode;
  
  /* Write to USART CR1 */
  USARTx->CR1 = tmpreg;
  
  /*---------------------------- USART CR3 Configuration -----------------------*/  
  tmpreg = USARTx->CR3;
  /* Clear CTSE and RTSE bits */
  tmpreg &= (uint32_t)~((uint32_t)CR3_CLEAR_MASK);
  
  /* Configure the USART HFC -------------------------------------------------*/
  /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  
  /* Write to USART CR3 */
  USARTx->CR3 = tmpreg;
  
  /*---------------------------- USART BRR Configuration -----------------------*/
  /* Configure the USART Baud Rate -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);
  
  if (USARTx == USART1)
  {
    apbclock = RCC_ClocksStatus.USART1CLK_Frequency;
  }
  else if (USARTx == USART2)
  {
    apbclock = RCC_ClocksStatus.USART2CLK_Frequency;
  }
  else
  {
    apbclock = RCC_ClocksStatus.PCLK_Frequency;
  }
  
  /* Determine the integer part */
  if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
  {
    /* (divider * 10) computing in case Oversampling mode is 8 Samples */
    divider = (uint32_t)((2 * apbclock) / (USART_InitStruct->USART_BaudRate));
    tmpreg  = (uint32_t)((2 * apbclock) % (USART_InitStruct->USART_BaudRate));
  }
  else /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
  {
    /* (divider * 10) computing in case Oversampling mode is 16 Samples */
    divider = (uint32_t)((apbclock) / (USART_InitStruct->USART_BaudRate));
    tmpreg  = (uint32_t)((apbclock) % (USART_InitStruct->USART_BaudRate));
  }
  
  /* round the divider : if fractional part i greater than 0.5 increment divider */
  if (tmpreg >=  (USART_InitStruct->USART_BaudRate) / 2)
  {
    divider++;
  } 
  
  /* Implement the divider in case Oversampling mode is 8 Samples */
  if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
  {
    /* get the LSB of divider and shift it to the right by 1 bit */
    tmpreg = (divider & (uint16_t)0x000F) >> 1;
    
    /* update the divider value */
    divider = (divider & (uint16_t)0xFFF0) | tmpreg;
  }
  
  /* Write to USART BRR */
  USARTx->BRR = (uint16_t)divider;
}
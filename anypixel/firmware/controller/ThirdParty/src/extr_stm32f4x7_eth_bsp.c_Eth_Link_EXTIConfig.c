#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* EXTI_LineCmd; int /*<<< orphan*/  EXTI_Trigger; int /*<<< orphan*/  EXTI_Mode; int /*<<< orphan*/  EXTI_Line; } ;
struct TYPE_8__ {int /*<<< orphan*/  GPIO_Pin; int /*<<< orphan*/  GPIO_PuPd; int /*<<< orphan*/  GPIO_Mode; } ;
struct TYPE_7__ {int NVIC_IRQChannelPreemptionPriority; void* NVIC_IRQChannelCmd; int /*<<< orphan*/  NVIC_IRQChannel; } ;
typedef  TYPE_1__ NVIC_InitTypeDef ;
typedef  TYPE_2__ GPIO_InitTypeDef ;
typedef  TYPE_3__ EXTI_InitTypeDef ;

/* Variables and functions */
 void* ENABLE ; 
 int /*<<< orphan*/  ETH_LINK_EXTI_LINE ; 
 int /*<<< orphan*/  ETH_LINK_EXTI_PIN_SOURCE ; 
 int /*<<< orphan*/  ETH_LINK_EXTI_PORT_SOURCE ; 
 int /*<<< orphan*/  ETH_LINK_GPIO_CLK ; 
 int /*<<< orphan*/  ETH_LINK_GPIO_PORT ; 
 int /*<<< orphan*/  ETH_LINK_PIN ; 
 int /*<<< orphan*/  EXTI15_10_IRQn ; 
 int /*<<< orphan*/  EXTI_Init (TYPE_3__*) ; 
 int /*<<< orphan*/  EXTI_Mode_Interrupt ; 
 int /*<<< orphan*/  EXTI_Trigger_Falling ; 
 int /*<<< orphan*/  GPIO_Init (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GPIO_Mode_IN ; 
 int /*<<< orphan*/  GPIO_PuPd_NOPULL ; 
 int /*<<< orphan*/  NVIC_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  RCC_AHB1PeriphClockCmd (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  RCC_APB2PeriphClockCmd (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  RCC_APB2Periph_SYSCFG ; 
 int /*<<< orphan*/  SYSCFG_EXTILineConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Eth_Link_EXTIConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the INT (PB14) Clock */
  RCC_AHB1PeriphClockCmd(ETH_LINK_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure INT pin as input */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = ETH_LINK_PIN;
  GPIO_Init(ETH_LINK_GPIO_PORT, &GPIO_InitStructure);

  /* Connect EXTI Line to INT Pin */
  SYSCFG_EXTILineConfig(ETH_LINK_EXTI_PORT_SOURCE, ETH_LINK_EXTI_PIN_SOURCE);

  /* Configure EXTI line */
  EXTI_InitStructure.EXTI_Line = ETH_LINK_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set the EXTI interrupt to priority 1*/
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
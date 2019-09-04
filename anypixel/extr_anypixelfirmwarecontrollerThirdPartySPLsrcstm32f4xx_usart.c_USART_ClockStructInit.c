#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  USART_LastBit; int /*<<< orphan*/  USART_CPHA; int /*<<< orphan*/  USART_CPOL; int /*<<< orphan*/  USART_Clock; } ;
typedef  TYPE_1__ USART_ClockInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USART_CPHA_1Edge ; 
 int /*<<< orphan*/  USART_CPOL_Low ; 
 int /*<<< orphan*/  USART_Clock_Disable ; 
 int /*<<< orphan*/  USART_LastBit_Disable ; 

void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  /* USART_ClockInitStruct members default value */
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}
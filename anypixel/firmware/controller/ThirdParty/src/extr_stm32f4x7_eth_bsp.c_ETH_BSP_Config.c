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
struct TYPE_3__ {int HCLK_Frequency; } ;
typedef  TYPE_1__ RCC_ClocksTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  BOARD_PHY_ADDRESS ; 
 int /*<<< orphan*/  ETH_GPIO_Config () ; 
 int /*<<< orphan*/  ETH_LINK_FLAG ; 
 int /*<<< orphan*/  ETH_MACDMA_Config () ; 
 int ETH_ReadPHYRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EthStatus ; 
 int /*<<< orphan*/  Eth_Link_EXTIConfig () ; 
 int /*<<< orphan*/  Eth_Link_PHYITConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVIC_SetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_SR ; 
 int /*<<< orphan*/  RCC_GetClocksFreq (TYPE_1__*) ; 
 int /*<<< orphan*/  SysTick_CLKSourceConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysTick_CLKSource_HCLK ; 
 int /*<<< orphan*/  SysTick_Config (int) ; 
 int /*<<< orphan*/  SysTick_IRQn ; 

void ETH_BSP_Config(void)
{
  RCC_ClocksTypeDef RCC_Clocks;

  /***************************************************************************
    NOTE:
         When using Systick to manage the delay in Ethernet driver, the Systick
         must be configured before Ethernet initialization and, the interrupt
         priority should be the highest one.
  *****************************************************************************/

  /* Configure Systick clock source as HCLK */
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

  /* SystTick configuration: an interrupt every 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

  /* Set Systick interrupt priority to 0*/
  NVIC_SetPriority (SysTick_IRQn, 0);

  /* Configure the GPIO ports for ethernet pins */
  ETH_GPIO_Config();

  /* Configure the Ethernet MAC/DMA */
  ETH_MACDMA_Config();

  /* Get Ethernet link status*/
  if(ETH_ReadPHYRegister(BOARD_PHY_ADDRESS, PHY_SR) & 1)
  {
    EthStatus |= ETH_LINK_FLAG;
  }

  /* Configure the PHY to generate an interrupt on change of link status */
  Eth_Link_PHYITConfig(BOARD_PHY_ADDRESS);

  /* Configure the EXTI for Ethernet link status. */
  Eth_Link_EXTIConfig();
}
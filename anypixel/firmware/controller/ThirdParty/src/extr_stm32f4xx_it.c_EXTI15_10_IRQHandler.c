#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  BOARD_PHY_ADDRESS ; 
 int /*<<< orphan*/  ETH_LINK_EXTI_LINE ; 
 int /*<<< orphan*/  EXTI_ClearITPendingBit (int /*<<< orphan*/ ) ; 
 scalar_t__ EXTI_GetITStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Eth_Link_ITHandler (int /*<<< orphan*/ ) ; 
 scalar_t__ RESET ; 

void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(ETH_LINK_EXTI_LINE) != RESET)
  {
    Eth_Link_ITHandler(BOARD_PHY_ADDRESS);
    /* Clear interrupt pending bit */
    EXTI_ClearITPendingBit(ETH_LINK_EXTI_LINE);
  }
}
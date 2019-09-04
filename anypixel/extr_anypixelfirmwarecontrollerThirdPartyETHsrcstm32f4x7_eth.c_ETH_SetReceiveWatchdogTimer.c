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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  DMARSWTR; } ;

/* Variables and functions */
 TYPE_1__* ETH ; 

void ETH_SetReceiveWatchdogTimer(uint8_t Value)
{
  /* Set the DMA Receive status watchdog timer register */
  ETH->DMARSWTR = Value;
}
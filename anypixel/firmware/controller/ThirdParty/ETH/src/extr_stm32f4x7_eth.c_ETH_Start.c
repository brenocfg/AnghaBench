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
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  ETH_DMAReceptionCmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_DMATransmissionCmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_FlushTransmitFIFO () ; 
 int /*<<< orphan*/  ETH_MACReceptionCmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_MACTransmissionCmd (int /*<<< orphan*/ ) ; 

void ETH_Start(void)
{
  /* Enable transmit state machine of the MAC for transmission on the MII */
  ETH_MACTransmissionCmd(ENABLE);

  /* Enable receive state machine of the MAC for reception from the MII */
  ETH_MACReceptionCmd(ENABLE);

  /* Flush Transmit FIFO */
  ETH_FlushTransmitFIFO();

  /* Start DMA transmission */
  ETH_DMATransmissionCmd(ENABLE);

  /* Start DMA reception */
  ETH_DMAReceptionCmd(ENABLE);
}
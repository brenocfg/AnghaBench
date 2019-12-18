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
 int /*<<< orphan*/  Start_DMA_Transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int TLC59401_CHANNELS ; 
 int /*<<< orphan*/  TM_SPI_WriteMulti (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rxpacket ; 
 int /*<<< orphan*/  txpacket ; 

void TLC59401_Send(void) {
    #ifndef USE_SPI_DMA
     TM_SPI_WriteMulti(txpacket, TLC59401_CHANNELS*3/2);
    #else
     Start_DMA_Transfer(txpacket, rxpacket, TLC59401_CHANNELS*3/2);
    #endif
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ ** tx_buf; int /*<<< orphan*/ ** rx_buf; void* descriptors; int /*<<< orphan*/ * ext_regs; int /*<<< orphan*/ * mac_regs; int /*<<< orphan*/ * dma_regs; } ;
typedef  TYPE_1__ emac_hal_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_DMA ; 
 int /*<<< orphan*/  EMAC_EXT ; 
 int /*<<< orphan*/  EMAC_MAC ; 

void emac_hal_init(emac_hal_context_t *hal, void *descriptors,
                   uint8_t **rx_buf, uint8_t **tx_buf)
{
    hal->dma_regs = &EMAC_DMA;
    hal->mac_regs = &EMAC_MAC;
    hal->ext_regs = &EMAC_EXT;
    hal->descriptors = descriptors;
    hal->rx_buf = rx_buf;
    hal->tx_buf = tx_buf;
}
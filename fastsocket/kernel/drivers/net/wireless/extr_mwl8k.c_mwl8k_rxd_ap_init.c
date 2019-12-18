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
struct mwl8k_rxd_ap {int /*<<< orphan*/  rx_ctrl; int /*<<< orphan*/  next_rxd_phys_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MWL8K_AP_RX_CTRL_OWNED_BY_HOST ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwl8k_rxd_ap_init(void *_rxd, dma_addr_t next_dma_addr)
{
	struct mwl8k_rxd_ap *rxd = _rxd;

	rxd->next_rxd_phys_addr = cpu_to_le32(next_dma_addr);
	rxd->rx_ctrl = MWL8K_AP_RX_CTRL_OWNED_BY_HOST;
}
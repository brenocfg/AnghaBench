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
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_DMA ; 
 int EIO ; 
 int ath5k_hw_stop_tx_dma (struct ath5k_hw*,unsigned int) ; 

int
ath5k_hw_stop_beacon_queue(struct ath5k_hw *ah, unsigned int queue)
{
	int ret;
	ret = ath5k_hw_stop_tx_dma(ah, queue);
	if (ret) {
		ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"beacon queue didn't stop !\n");
		return -EIO;
	}
	return 0;
}
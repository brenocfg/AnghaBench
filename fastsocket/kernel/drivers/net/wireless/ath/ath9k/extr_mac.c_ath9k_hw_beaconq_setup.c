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
struct TYPE_2__ {int hw_caps; } ;
struct ath_hw {TYPE_1__ caps; } ;
struct ath9k_tx_queue_info {int tqi_aifs; int /*<<< orphan*/  tqi_qflags; scalar_t__ tqi_cwmax; scalar_t__ tqi_cwmin; } ;
typedef  int /*<<< orphan*/  qi ;

/* Variables and functions */
 int ATH9K_HW_CAP_EDMA ; 
 int /*<<< orphan*/  ATH9K_TX_QUEUE_BEACON ; 
 int /*<<< orphan*/  TXQ_FLAG_TXINT_ENABLE ; 
 int ath9k_hw_setuptxqueue (struct ath_hw*,int /*<<< orphan*/ ,struct ath9k_tx_queue_info*) ; 
 int /*<<< orphan*/  memset (struct ath9k_tx_queue_info*,int /*<<< orphan*/ ,int) ; 

int ath9k_hw_beaconq_setup(struct ath_hw *ah)
{
	struct ath9k_tx_queue_info qi;

	memset(&qi, 0, sizeof(qi));
	qi.tqi_aifs = 1;
	qi.tqi_cwmin = 0;
	qi.tqi_cwmax = 0;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		qi.tqi_qflags = TXQ_FLAG_TXINT_ENABLE;

	return ath9k_hw_setuptxqueue(ah, ATH9K_TX_QUEUE_BEACON, &qi);
}
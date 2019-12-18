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
struct ath5k_txq_info {int dummy; } ;
struct ath5k_hw {int /*<<< orphan*/ * ah_txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct ath5k_txq_info*,int /*<<< orphan*/ *,int) ; 

int
ath5k_hw_get_tx_queueprops(struct ath5k_hw *ah, int queue,
		struct ath5k_txq_info *queue_info)
{
	memcpy(queue_info, &ah->ah_txq[queue], sizeof(struct ath5k_txq_info));
	return 0;
}
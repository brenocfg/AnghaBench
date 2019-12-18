#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  q_tx_num; } ;
struct TYPE_5__ {TYPE_1__ cap_queues; } ;
struct ath5k_hw {scalar_t__ ah_version; TYPE_3__* ah_txq; TYPE_2__ ah_capabilities; } ;
struct TYPE_6__ {int tqi_type; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_ASSERT_ENTRY (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_NOQCU_TXDP0 ; 
 int /*<<< orphan*/  AR5K_NOQCU_TXDP1 ; 
 int /*<<< orphan*/  AR5K_QCU_TXE ; 
 int /*<<< orphan*/  AR5K_QUEUE_TXDP (unsigned int) ; 
 scalar_t__ AR5K_REG_READ_Q (struct ath5k_hw*,int /*<<< orphan*/ ,unsigned int) ; 
#define  AR5K_TX_QUEUE_BEACON 130 
#define  AR5K_TX_QUEUE_CAB 129 
#define  AR5K_TX_QUEUE_DATA 128 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ath5k_hw_set_txdp(struct ath5k_hw *ah, unsigned int queue, u32 phys_addr)
{
	u16 tx_reg;

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	/*
	 * Set the transmit queue descriptor pointer register by type
	 * on 5210
	 */
	if (ah->ah_version == AR5K_AR5210) {
		switch (ah->ah_txq[queue].tqi_type) {
		case AR5K_TX_QUEUE_DATA:
			tx_reg = AR5K_NOQCU_TXDP0;
			break;
		case AR5K_TX_QUEUE_BEACON:
		case AR5K_TX_QUEUE_CAB:
			tx_reg = AR5K_NOQCU_TXDP1;
			break;
		default:
			return -EINVAL;
		}
	} else {
		/*
		 * Set the transmit queue descriptor pointer for
		 * the selected queue on QCU for 5211+
		 * (this won't work if the queue is still active)
		 */
		if (AR5K_REG_READ_Q(ah, AR5K_QCU_TXE, queue))
			return -EIO;

		tx_reg = AR5K_QUEUE_TXDP(queue);
	}

	/* Set descriptor pointer */
	ath5k_hw_reg_write(ah, phys_addr, tx_reg);

	return 0;
}
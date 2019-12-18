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
typedef  int u32 ;
struct qlcnic_host_tx_ring {int producer; int /*<<< orphan*/  txq; int /*<<< orphan*/  num_desc; int /*<<< orphan*/ * desc_head; struct qlcnic_cmd_buffer* cmd_buf_arr; } ;
struct qlcnic_cmd_buffer {scalar_t__ frag_count; int /*<<< orphan*/ * skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  xmit_off; } ;
struct qlcnic_adapter {TYPE_1__ stats; struct qlcnic_host_tx_ring* tx_ring; int /*<<< orphan*/  state; } ;
struct cmd_desc_type0 {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int TX_STOP_THRESH ; 
 int /*<<< orphan*/  __QLCNIC_FW_ATTACHED ; 
 int /*<<< orphan*/  __netif_tx_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock_bh (int /*<<< orphan*/ ) ; 
 int get_next_index (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cmd_desc_type0*,int) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (int /*<<< orphan*/ ) ; 
 int qlcnic_tx_avail (struct qlcnic_host_tx_ring*) ; 
 int /*<<< orphan*/  qlcnic_update_cmd_producer (struct qlcnic_host_tx_ring*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qlcnic_send_cmd_descs(struct qlcnic_adapter *adapter,
		struct cmd_desc_type0 *cmd_desc_arr, int nr_desc)
{
	u32 i, producer;
	struct qlcnic_cmd_buffer *pbuf;
	struct cmd_desc_type0 *cmd_desc;
	struct qlcnic_host_tx_ring *tx_ring;

	i = 0;

	if (!test_bit(__QLCNIC_FW_ATTACHED, &adapter->state))
		return -EIO;

	tx_ring = adapter->tx_ring;
	__netif_tx_lock_bh(tx_ring->txq);

	producer = tx_ring->producer;

	if (nr_desc >= qlcnic_tx_avail(tx_ring)) {
		netif_tx_stop_queue(tx_ring->txq);
		smp_mb();
		if (qlcnic_tx_avail(tx_ring) > nr_desc) {
			if (qlcnic_tx_avail(tx_ring) > TX_STOP_THRESH)
				netif_tx_wake_queue(tx_ring->txq);
		} else {
			adapter->stats.xmit_off++;
			__netif_tx_unlock_bh(tx_ring->txq);
			return -EBUSY;
		}
	}

	do {
		cmd_desc = &cmd_desc_arr[i];

		pbuf = &tx_ring->cmd_buf_arr[producer];
		pbuf->skb = NULL;
		pbuf->frag_count = 0;

		memcpy(&tx_ring->desc_head[producer],
		       cmd_desc, sizeof(struct cmd_desc_type0));

		producer = get_next_index(producer, tx_ring->num_desc);
		i++;

	} while (i != nr_desc);

	tx_ring->producer = producer;

	qlcnic_update_cmd_producer(tx_ring);

	__netif_tx_unlock_bh(tx_ring->txq);

	return 0;
}
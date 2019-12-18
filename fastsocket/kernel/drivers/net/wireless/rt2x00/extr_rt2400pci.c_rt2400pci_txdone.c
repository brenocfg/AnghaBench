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
typedef  int /*<<< orphan*/  u32 ;
struct txdone_entry_desc {int retry; scalar_t__ flags; } ;
struct rt2x00_dev {int dummy; } ;
struct queue_entry_priv_mmio {int /*<<< orphan*/  desc; } ;
struct queue_entry {struct queue_entry_priv_mmio* priv_data; } ;
struct data_queue {int dummy; } ;
typedef  enum data_queue_qid { ____Placeholder_data_queue_qid } data_queue_qid ;

/* Variables and functions */
 int /*<<< orphan*/  Q_INDEX_DONE ; 
 int /*<<< orphan*/  TXDONE_EXCESSIVE_RETRY ; 
 int /*<<< orphan*/  TXDONE_FAILURE ; 
 int /*<<< orphan*/  TXDONE_SUCCESS ; 
 int /*<<< orphan*/  TXD_W0_OWNER_NIC ; 
 int /*<<< orphan*/  TXD_W0_RESULT ; 
 int /*<<< orphan*/  TXD_W0_RETRY_COUNT ; 
 int /*<<< orphan*/  TXD_W0_VALID ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00lib_txdone (struct queue_entry*,struct txdone_entry_desc*) ; 
 int /*<<< orphan*/  rt2x00queue_empty (struct data_queue*) ; 
 struct queue_entry* rt2x00queue_get_entry (struct data_queue*,int /*<<< orphan*/ ) ; 
 struct data_queue* rt2x00queue_get_tx_queue (struct rt2x00_dev*,int const) ; 

__attribute__((used)) static void rt2400pci_txdone(struct rt2x00_dev *rt2x00dev,
			     const enum data_queue_qid queue_idx)
{
	struct data_queue *queue = rt2x00queue_get_tx_queue(rt2x00dev, queue_idx);
	struct queue_entry_priv_mmio *entry_priv;
	struct queue_entry *entry;
	struct txdone_entry_desc txdesc;
	u32 word;

	while (!rt2x00queue_empty(queue)) {
		entry = rt2x00queue_get_entry(queue, Q_INDEX_DONE);
		entry_priv = entry->priv_data;
		rt2x00_desc_read(entry_priv->desc, 0, &word);

		if (rt2x00_get_field32(word, TXD_W0_OWNER_NIC) ||
		    !rt2x00_get_field32(word, TXD_W0_VALID))
			break;

		/*
		 * Obtain the status about this packet.
		 */
		txdesc.flags = 0;
		switch (rt2x00_get_field32(word, TXD_W0_RESULT)) {
		case 0: /* Success */
		case 1: /* Success with retry */
			__set_bit(TXDONE_SUCCESS, &txdesc.flags);
			break;
		case 2: /* Failure, excessive retries */
			__set_bit(TXDONE_EXCESSIVE_RETRY, &txdesc.flags);
			/* Don't break, this is a failed frame! */
		default: /* Failure */
			__set_bit(TXDONE_FAILURE, &txdesc.flags);
		}
		txdesc.retry = rt2x00_get_field32(word, TXD_W0_RETRY_COUNT);

		rt2x00lib_txdone(entry, &txdesc);
	}
}
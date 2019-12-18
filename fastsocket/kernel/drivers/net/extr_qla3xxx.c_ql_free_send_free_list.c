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
struct ql_tx_buf_cb {int /*<<< orphan*/ * oal; } ;
struct ql3_adapter {struct ql_tx_buf_cb* tx_buf; } ;

/* Variables and functions */
 int NUM_REQ_Q_ENTRIES ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_free_send_free_list(struct ql3_adapter *qdev)
{
	struct ql_tx_buf_cb *tx_cb;
	int i;

	tx_cb = &qdev->tx_buf[0];
	for (i = 0; i < NUM_REQ_Q_ENTRIES; i++) {
		if (tx_cb->oal) {
			kfree(tx_cb->oal);
			tx_cb->oal = NULL;
		}
		tx_cb++;
	}
}
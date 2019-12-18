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
typedef  size_t u_int32_t ;
typedef  int /*<<< orphan*/ * mbuf_tx_compl_func ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 size_t MAX_MBUF_TX_COMPL_FUNC ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_unlock_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** mbuf_tx_compl_table ; 
 int /*<<< orphan*/  mbuf_tx_compl_tbl_lock ; 

mbuf_tx_compl_func
m_get_tx_compl_callback(u_int32_t idx)
{
	mbuf_tx_compl_func cb;

	if (idx >= MAX_MBUF_TX_COMPL_FUNC) {
		ASSERT(0);
		return (NULL);
	}
	lck_rw_lock_shared(mbuf_tx_compl_tbl_lock);
	cb = mbuf_tx_compl_table[idx];
	lck_rw_unlock_shared(mbuf_tx_compl_tbl_lock);
	return (cb);
}
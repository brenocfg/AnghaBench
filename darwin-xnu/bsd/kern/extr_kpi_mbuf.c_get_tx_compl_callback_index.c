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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  mbuf_tx_compl_func ;

/* Variables and functions */
 int /*<<< orphan*/  get_tx_compl_callback_index_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_unlock_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_tx_compl_tbl_lock ; 

__attribute__((used)) static u_int32_t
get_tx_compl_callback_index(mbuf_tx_compl_func callback)
{
	u_int32_t i;

	lck_rw_lock_shared(mbuf_tx_compl_tbl_lock);

	i = get_tx_compl_callback_index_locked(callback);

	lck_rw_unlock_shared(mbuf_tx_compl_tbl_lock);

	return (i);
}
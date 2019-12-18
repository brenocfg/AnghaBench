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
typedef  scalar_t__ mbuf_tx_compl_func ;

/* Variables and functions */
 size_t MAX_MBUF_TX_COMPL_FUNC ; 
 size_t UINT32_MAX ; 
 scalar_t__* mbuf_tx_compl_table ; 

__attribute__((used)) static u_int32_t
get_tx_compl_callback_index_locked(mbuf_tx_compl_func callback)
{
	u_int32_t i;

	for (i = 0; i < MAX_MBUF_TX_COMPL_FUNC; i++) {
		if (mbuf_tx_compl_table[i] == callback) {
			return (i);
		}
	}
	return (UINT32_MAX);
}
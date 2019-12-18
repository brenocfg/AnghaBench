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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static bool ath9k_hw_check_dcs(u32 dma_dbg, u32 num_dcu_states,
			       int *hang_state, int *hang_pos)
{
	static u32 dcu_chain_state[] = {5, 6, 9}; /* DCU chain stuck states */
	u32 chain_state, dcs_pos, i;

	for (dcs_pos = 0; dcs_pos < num_dcu_states; dcs_pos++) {
		chain_state = (dma_dbg >> (5 * dcs_pos)) & 0x1f;
		for (i = 0; i < 3; i++) {
			if (chain_state == dcu_chain_state[i]) {
				*hang_state = chain_state;
				*hang_pos = dcs_pos;
				return true;
			}
		}
	}
	return false;
}
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
struct e1000_hw {int collision_delta; int ifs_ratio; int tx_packet_delta; int in_ifs_mode; scalar_t__ current_ifs_val; scalar_t__ ifs_max_val; scalar_t__ ifs_min_val; scalar_t__ ifs_step_size; scalar_t__ adaptive_ifs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIT ; 
 int MIN_NUM_XMITS ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,scalar_t__) ; 

void e1000_update_adaptive(struct e1000_hw *hw)
{
	e_dbg("e1000_update_adaptive");

	if (hw->adaptive_ifs) {
		if ((hw->collision_delta *hw->ifs_ratio) > hw->tx_packet_delta) {
			if (hw->tx_packet_delta > MIN_NUM_XMITS) {
				hw->in_ifs_mode = true;
				if (hw->current_ifs_val < hw->ifs_max_val) {
					if (hw->current_ifs_val == 0)
						hw->current_ifs_val =
						    hw->ifs_min_val;
					else
						hw->current_ifs_val +=
						    hw->ifs_step_size;
					ew32(AIT, hw->current_ifs_val);
				}
			}
		} else {
			if (hw->in_ifs_mode
			    && (hw->tx_packet_delta <= MIN_NUM_XMITS)) {
				hw->current_ifs_val = 0;
				hw->in_ifs_mode = false;
				ew32(AIT, 0);
			}
		}
	} else {
		e_dbg("Not in Adaptive IFS mode!\n");
	}
}
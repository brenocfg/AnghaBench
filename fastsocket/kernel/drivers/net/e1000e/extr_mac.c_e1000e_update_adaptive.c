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
struct e1000_mac_info {int collision_delta; int ifs_ratio; int tx_packet_delta; int in_ifs_mode; scalar_t__ current_ifs_val; scalar_t__ ifs_max_val; scalar_t__ ifs_min_val; scalar_t__ ifs_step_size; int /*<<< orphan*/  adaptive_ifs; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIT ; 
 int MIN_NUM_XMITS ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,scalar_t__) ; 

void e1000e_update_adaptive(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;

	if (!mac->adaptive_ifs) {
		e_dbg("Not in Adaptive IFS mode!\n");
		return;
	}

	if ((mac->collision_delta * mac->ifs_ratio) > mac->tx_packet_delta) {
		if (mac->tx_packet_delta > MIN_NUM_XMITS) {
			mac->in_ifs_mode = true;
			if (mac->current_ifs_val < mac->ifs_max_val) {
				if (!mac->current_ifs_val)
					mac->current_ifs_val = mac->ifs_min_val;
				else
					mac->current_ifs_val +=
					    mac->ifs_step_size;
				ew32(AIT, mac->current_ifs_val);
			}
		}
	} else {
		if (mac->in_ifs_mode &&
		    (mac->tx_packet_delta <= MIN_NUM_XMITS)) {
			mac->current_ifs_val = 0;
			mac->in_ifs_mode = false;
			ew32(AIT, 0);
		}
	}
}
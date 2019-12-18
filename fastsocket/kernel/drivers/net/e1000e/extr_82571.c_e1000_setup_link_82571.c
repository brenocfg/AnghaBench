#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  requested_mode; } ;
struct TYPE_3__ {int type; } ;
struct e1000_hw {TYPE_2__ fc; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  e1000_82573 130 
#define  e1000_82574 129 
#define  e1000_82583 128 
 int /*<<< orphan*/  e1000_fc_default ; 
 int /*<<< orphan*/  e1000_fc_full ; 
 int /*<<< orphan*/  e1000e_setup_link_generic (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_setup_link_82571(struct e1000_hw *hw)
{
	/* 82573 does not have a word in the NVM to determine
	 * the default flow control setting, so we explicitly
	 * set it to full.
	 */
	switch (hw->mac.type) {
	case e1000_82573:
	case e1000_82574:
	case e1000_82583:
		if (hw->fc.requested_mode == e1000_fc_default)
			hw->fc.requested_mode = e1000_fc_full;
		break;
	default:
		break;
	}

	return e1000e_setup_link_generic(hw);
}
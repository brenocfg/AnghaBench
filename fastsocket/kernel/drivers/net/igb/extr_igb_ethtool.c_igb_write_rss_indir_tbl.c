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
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int* rss_indir_tbl; int /*<<< orphan*/  vfs_allocated_count; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_RETA (int /*<<< orphan*/ ) ; 
 int IGB_RETA_SIZE ; 
#define  e1000_82575 129 
#define  e1000_82576 128 
 int /*<<< orphan*/  wr32 (int,int) ; 

void igb_write_rss_indir_tbl(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 reg = E1000_RETA(0);
	u32 shift = 0;
	int i = 0;

	switch (hw->mac.type) {
	case e1000_82575:
		shift = 6;
		break;
	case e1000_82576:
		/* 82576 supports 2 RSS queues for SR-IOV */
		if (adapter->vfs_allocated_count)
			shift = 3;
		break;
	default:
		break;
	}

	while (i < IGB_RETA_SIZE) {
		u32 val = 0;
		int j;

		for (j = 3; j >= 0; j--) {
			val <<= 8;
			val |= adapter->rss_indir_tbl[i + j];
		}

		wr32(reg, val << shift);
		reg += 4;
		i += 4;
	}
}
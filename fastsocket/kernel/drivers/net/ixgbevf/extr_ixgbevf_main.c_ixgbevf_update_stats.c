#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ base_vfmprc; scalar_t__ vfmprc; int /*<<< orphan*/  last_vfmprc; int /*<<< orphan*/  vfgotc; int /*<<< orphan*/  last_vfgotc; int /*<<< orphan*/  vfgorc; int /*<<< orphan*/  last_vfgorc; scalar_t__ vfgptc; int /*<<< orphan*/  last_vfgptc; scalar_t__ vfgprc; int /*<<< orphan*/  last_vfgprc; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {TYPE_3__ stats; TYPE_2__* netdev; int /*<<< orphan*/  link_up; struct ixgbe_hw hw; } ;
struct TYPE_4__ {scalar_t__ multicast; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_VFGORC_LSB ; 
 int /*<<< orphan*/  IXGBE_VFGORC_MSB ; 
 int /*<<< orphan*/  IXGBE_VFGOTC_LSB ; 
 int /*<<< orphan*/  IXGBE_VFGOTC_MSB ; 
 int /*<<< orphan*/  IXGBE_VFGPRC ; 
 int /*<<< orphan*/  IXGBE_VFGPTC ; 
 int /*<<< orphan*/  IXGBE_VFMPRC ; 
 int /*<<< orphan*/  UPDATE_VF_COUNTER_32bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UPDATE_VF_COUNTER_36bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ixgbevf_update_stats(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;

	if (!adapter->link_up)
		return;

	UPDATE_VF_COUNTER_32bit(IXGBE_VFGPRC, adapter->stats.last_vfgprc,
				adapter->stats.vfgprc);
	UPDATE_VF_COUNTER_32bit(IXGBE_VFGPTC, adapter->stats.last_vfgptc,
				adapter->stats.vfgptc);
	UPDATE_VF_COUNTER_36bit(IXGBE_VFGORC_LSB, IXGBE_VFGORC_MSB,
				adapter->stats.last_vfgorc,
				adapter->stats.vfgorc);
	UPDATE_VF_COUNTER_36bit(IXGBE_VFGOTC_LSB, IXGBE_VFGOTC_MSB,
				adapter->stats.last_vfgotc,
				adapter->stats.vfgotc);
	UPDATE_VF_COUNTER_32bit(IXGBE_VFMPRC, adapter->stats.last_vfmprc,
				adapter->stats.vfmprc);

	/* Fill out the OS statistics structure */
	adapter->netdev->stats.multicast = adapter->stats.vfmprc -
		adapter->stats.base_vfmprc;
}
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
struct TYPE_2__ {scalar_t__ base_vfmprc; scalar_t__ vfmprc; int /*<<< orphan*/  saved_reset_vfmprc; scalar_t__ base_vfgotc; scalar_t__ vfgotc; int /*<<< orphan*/  saved_reset_vfgotc; scalar_t__ base_vfgorc; scalar_t__ vfgorc; int /*<<< orphan*/  saved_reset_vfgorc; scalar_t__ base_vfgptc; scalar_t__ vfgptc; int /*<<< orphan*/  saved_reset_vfgptc; scalar_t__ base_vfgprc; scalar_t__ vfgprc; int /*<<< orphan*/  saved_reset_vfgprc; } ;
struct ixgbevf_adapter {TYPE_1__ stats; } ;

/* Variables and functions */

__attribute__((used)) static void ixgbevf_save_reset_stats(struct ixgbevf_adapter *adapter)
{
	/* Only save pre-reset stats if there are some */
	if (adapter->stats.vfgprc || adapter->stats.vfgptc) {
		adapter->stats.saved_reset_vfgprc += adapter->stats.vfgprc -
			adapter->stats.base_vfgprc;
		adapter->stats.saved_reset_vfgptc += adapter->stats.vfgptc -
			adapter->stats.base_vfgptc;
		adapter->stats.saved_reset_vfgorc += adapter->stats.vfgorc -
			adapter->stats.base_vfgorc;
		adapter->stats.saved_reset_vfgotc += adapter->stats.vfgotc -
			adapter->stats.base_vfgotc;
		adapter->stats.saved_reset_vfmprc += adapter->stats.vfmprc -
			adapter->stats.base_vfmprc;
	}
}
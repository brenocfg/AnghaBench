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
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_unencrypted ; 
 int /*<<< orphan*/  hw_queues ; 
 int /*<<< orphan*/  rc_rateidx_mask_2ghz ; 
 int /*<<< orphan*/  rc_rateidx_mask_5ghz ; 
 int /*<<< orphan*/  rc_rateidx_mcs_mask_2ghz ; 
 int /*<<< orphan*/  rc_rateidx_mcs_mask_5ghz ; 

__attribute__((used)) static void add_common_files(struct ieee80211_sub_if_data *sdata)
{
	DEBUGFS_ADD(drop_unencrypted);
	DEBUGFS_ADD(rc_rateidx_mask_2ghz);
	DEBUGFS_ADD(rc_rateidx_mask_5ghz);
	DEBUGFS_ADD(rc_rateidx_mcs_mask_2ghz);
	DEBUGFS_ADD(rc_rateidx_mcs_mask_5ghz);
	DEBUGFS_ADD(hw_queues);
}
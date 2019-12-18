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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
struct dentry {int dummy; } ;
struct ath_node {int /*<<< orphan*/  node_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct ath_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_node_stat ; 

void ath9k_sta_add_debugfs(struct ieee80211_hw *hw,
			   struct ieee80211_vif *vif,
			   struct ieee80211_sta *sta,
			   struct dentry *dir)
{
	struct ath_node *an = (struct ath_node *)sta->drv_priv;
	an->node_stat = debugfs_create_file("node_stat", S_IRUGO,
					    dir, an, &fops_node_stat);
}
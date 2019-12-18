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
typedef  int u8 ;

/* Variables and functions */
#define  NL80211_DFS_ETSI 130 
#define  NL80211_DFS_FCC 129 
#define  NL80211_DFS_JP 128 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void print_dfs_region(u8 dfs_region)
{
	if (!dfs_region)
		return;

	switch (dfs_region) {
	case NL80211_DFS_FCC:
		pr_info(" DFS Master region FCC");
		break;
	case NL80211_DFS_ETSI:
		pr_info(" DFS Master region ETSI");
		break;
	case NL80211_DFS_JP:
		pr_info(" DFS Master region JP");
		break;
	default:
		pr_info(" DFS Master region Unknown");
		break;
	}
}
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
typedef  size_t u32 ;
struct radar_types {int region; } ;
typedef  enum nl80211_dfs_regions { ____Placeholder_nl80211_dfs_regions } nl80211_dfs_regions ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct radar_types const**) ; 
 struct radar_types const** dfs_domains ; 

__attribute__((used)) static const struct radar_types *
get_dfs_domain_radar_types(enum nl80211_dfs_regions region)
{
	u32 i;
	for (i = 0; i < ARRAY_SIZE(dfs_domains); i++) {
		if (dfs_domains[i]->region == region)
			return dfs_domains[i];
	}
	return NULL;
}
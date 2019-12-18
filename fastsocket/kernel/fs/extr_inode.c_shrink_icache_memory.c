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
struct shrinker {int dummy; } ;
typedef  int gfp_t ;
struct TYPE_2__ {int nr_unused; } ;

/* Variables and functions */
 int __GFP_FS ; 
 TYPE_1__ inodes_stat ; 
 int /*<<< orphan*/  prune_icache (int) ; 
 int sysctl_vfs_cache_pressure ; 

__attribute__((used)) static int shrink_icache_memory(struct shrinker *shrink, int nr, gfp_t gfp_mask)
{
	if (nr) {
		/*
		 * Nasty deadlock avoidance.  We may hold various FS locks,
		 * and we don't want to recurse into the FS that called us
		 * in clear_inode() and friends..
		 */
		if (!(gfp_mask & __GFP_FS))
			return -1;
		prune_icache(nr);
	}
	return (inodes_stat.nr_unused / 100) * sysctl_vfs_cache_pressure;
}
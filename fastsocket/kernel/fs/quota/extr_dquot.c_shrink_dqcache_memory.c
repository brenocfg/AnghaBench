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
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int free_dquots; } ;

/* Variables and functions */
 int /*<<< orphan*/  dq_list_lock ; 
 TYPE_1__ dqstats ; 
 int /*<<< orphan*/  prune_dqcache (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sysctl_vfs_cache_pressure ; 

__attribute__((used)) static int shrink_dqcache_memory(struct shrinker *shrink, int nr, gfp_t gfp_mask)
{
	if (nr) {
		spin_lock(&dq_list_lock);
		prune_dqcache(nr);
		spin_unlock(&dq_list_lock);
	}
	return (dqstats.free_dquots / 100) * sysctl_vfs_cache_pressure;
}
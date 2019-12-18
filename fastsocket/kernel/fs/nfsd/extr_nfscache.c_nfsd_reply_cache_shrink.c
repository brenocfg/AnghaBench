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
struct shrinker {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  cache_lock ; 
 unsigned int num_drc_entries ; 
 int /*<<< orphan*/  prune_cache_entries () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsd_reply_cache_shrink(struct shrinker *shrink, int nr_to_scan,
			gfp_t gfp_mask)
{
	unsigned int num;

	spin_lock(&cache_lock);
	if (nr_to_scan)
		prune_cache_entries();
	num = num_drc_entries;
	spin_unlock(&cache_lock);

	return num;
}
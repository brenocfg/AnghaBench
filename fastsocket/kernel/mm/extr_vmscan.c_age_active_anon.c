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
struct zone {int dummy; } ;
struct scan_control {int dummy; } ;
struct mem_cgroup_zone {struct zone* zone; struct mem_cgroup* mem_cgroup; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_CLUSTER_MAX ; 
 scalar_t__ inactive_anon_is_low (struct mem_cgroup_zone*) ; 
 struct mem_cgroup* mem_cgroup_iter (int /*<<< orphan*/ *,struct mem_cgroup*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shrink_active_list (int /*<<< orphan*/ ,struct mem_cgroup_zone*,struct scan_control*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_swap_pages ; 

__attribute__((used)) static void age_active_anon(struct zone *zone, struct scan_control *sc,
			    int priority)
{
	struct mem_cgroup *memcg;

	if (!total_swap_pages)
		return;

	memcg = mem_cgroup_iter(NULL, NULL, NULL);
	do {
		struct mem_cgroup_zone mz = {
			.mem_cgroup = memcg,
			.zone = zone,
		};

		if (inactive_anon_is_low(&mz))
			shrink_active_list(SWAP_CLUSTER_MAX, &mz,
					   sc, priority, 0);

		memcg = mem_cgroup_iter(NULL, memcg, NULL);
	} while (memcg);
}
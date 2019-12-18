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
struct svc_rdma_req_map {int /*<<< orphan*/ * frmr; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct svc_rdma_req_map* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rdma_map_cachep ; 

struct svc_rdma_req_map *svc_rdma_get_req_map(void)
{
	struct svc_rdma_req_map *map;
	while (1) {
		map = kmem_cache_alloc(svc_rdma_map_cachep, GFP_KERNEL);
		if (map)
			break;
		schedule_timeout_uninterruptible(msecs_to_jiffies(500));
	}
	map->count = 0;
	map->frmr = NULL;
	return map;
}
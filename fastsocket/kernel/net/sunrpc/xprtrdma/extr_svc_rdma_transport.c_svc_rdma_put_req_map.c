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
struct svc_rdma_req_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct svc_rdma_req_map*) ; 
 int /*<<< orphan*/  svc_rdma_map_cachep ; 

void svc_rdma_put_req_map(struct svc_rdma_req_map *map)
{
	kmem_cache_free(svc_rdma_map_cachep, map);
}
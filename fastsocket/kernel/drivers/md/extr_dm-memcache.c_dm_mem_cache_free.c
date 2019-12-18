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
struct dm_mem_cache_object {int dummy; } ;
struct dm_mem_cache_client {int /*<<< orphan*/  objs_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_chunks (struct dm_mem_cache_client*,struct dm_mem_cache_object*) ; 
 int /*<<< orphan*/  mempool_free (struct dm_mem_cache_object*,int /*<<< orphan*/ ) ; 

void dm_mem_cache_free(struct dm_mem_cache_client *cl,
		       struct dm_mem_cache_object *obj)
{
	free_chunks(cl, obj);
	mempool_free(obj, cl->objs_pool);
}
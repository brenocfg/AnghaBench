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
struct dm_mem_cache_client {scalar_t__ free_pages; scalar_t__ total_pages; int /*<<< orphan*/  objs_pool; int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  free_cache_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dm_mem_cache_client*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

void dm_mem_cache_client_destroy(struct dm_mem_cache_client *cl)
{
	BUG_ON(cl->free_pages != cl->total_pages);
	free_cache_pages(cl->free_list);
	mempool_destroy(cl->objs_pool);
	kfree(cl);
}
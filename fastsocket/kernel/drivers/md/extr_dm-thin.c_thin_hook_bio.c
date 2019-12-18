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
struct thin_c {struct pool* pool; } ;
struct pool {int /*<<< orphan*/  endio_hook_pool; } ;
struct dm_thin_endio_hook {struct bio* bio; int /*<<< orphan*/ * overwrite_mapping; int /*<<< orphan*/ * all_io_entry; int /*<<< orphan*/ * shared_read_entry; struct thin_c* tc; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 struct dm_thin_endio_hook* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dm_thin_endio_hook *thin_hook_bio(struct thin_c *tc, struct bio *bio)
{
	struct pool *pool = tc->pool;
	struct dm_thin_endio_hook *h = mempool_alloc(pool->endio_hook_pool, GFP_NOIO);

	h->tc = tc;
	h->shared_read_entry = NULL;
	h->all_io_entry = NULL;
	h->overwrite_mapping = NULL;
	h->bio = bio;

	return h;
}
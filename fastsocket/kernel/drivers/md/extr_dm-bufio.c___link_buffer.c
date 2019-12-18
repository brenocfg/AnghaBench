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
struct dm_bufio_client {int /*<<< orphan*/ * cache_hash; int /*<<< orphan*/ * lru; int /*<<< orphan*/ * n_buffers; } ;
struct dm_buffer {int list_mode; int /*<<< orphan*/  last_accessed; int /*<<< orphan*/  hash_list; int /*<<< orphan*/  lru_list; int /*<<< orphan*/  block; struct dm_bufio_client* c; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 size_t DM_BUFIO_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __link_buffer(struct dm_buffer *b, sector_t block, int dirty)
{
	struct dm_bufio_client *c = b->c;

	c->n_buffers[dirty]++;
	b->block = block;
	b->list_mode = dirty;
	list_add(&b->lru_list, &c->lru[dirty]);
	hlist_add_head(&b->hash_list, &c->cache_hash[DM_BUFIO_HASH(block)]);
	b->last_accessed = jiffies;
}
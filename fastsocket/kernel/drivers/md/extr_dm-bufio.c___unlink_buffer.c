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
struct dm_bufio_client {int /*<<< orphan*/ * n_buffers; } ;
struct dm_buffer {size_t list_mode; int /*<<< orphan*/  lru_list; int /*<<< orphan*/  hash_list; struct dm_bufio_client* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __unlink_buffer(struct dm_buffer *b)
{
	struct dm_bufio_client *c = b->c;

	BUG_ON(!c->n_buffers[b->list_mode]);

	c->n_buffers[b->list_mode]--;
	hlist_del(&b->hash_list);
	list_del(&b->lru_list);
}
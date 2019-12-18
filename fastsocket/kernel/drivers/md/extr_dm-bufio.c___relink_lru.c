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
struct dm_bufio_client {int /*<<< orphan*/ * lru; int /*<<< orphan*/ * n_buffers; } ;
struct dm_buffer {size_t list_mode; int /*<<< orphan*/  lru_list; struct dm_bufio_client* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __relink_lru(struct dm_buffer *b, int dirty)
{
	struct dm_bufio_client *c = b->c;

	BUG_ON(!c->n_buffers[b->list_mode]);

	c->n_buffers[b->list_mode]--;
	c->n_buffers[dirty]++;
	b->list_mode = dirty;
	list_move(&b->lru_list, &c->lru[dirty]);
}
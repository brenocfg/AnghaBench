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
struct pktcdvd_device {scalar_t__ bio_queue_size; int /*<<< orphan*/  rb_pool; int /*<<< orphan*/  bio_queue; } ;
struct pkt_rb_node {int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mempool_free (struct pkt_rb_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_rbtree_erase(struct pktcdvd_device *pd, struct pkt_rb_node *node)
{
	rb_erase(&node->rb_node, &pd->bio_queue);
	mempool_free(node, pd->rb_pool);
	pd->bio_queue_size--;
	BUG_ON(pd->bio_queue_size < 0);
}
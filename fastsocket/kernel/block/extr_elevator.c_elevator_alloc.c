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
struct request_queue {int /*<<< orphan*/  node; } ;
struct hlist_head {int dummy; } ;
struct elevator_type {int /*<<< orphan*/  ops; } ;
struct elevator_queue {int /*<<< orphan*/ * hash; int /*<<< orphan*/  sysfs_lock; int /*<<< orphan*/  kobj; struct elevator_type* elevator_type; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ELV_HASH_ENTRIES ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  elevator_put (struct elevator_type*) ; 
 int /*<<< orphan*/  elv_ktype ; 
 int /*<<< orphan*/  kfree (struct elevator_queue*) ; 
 void* kmalloc_node (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct elevator_queue *elevator_alloc(struct request_queue *q,
				  struct elevator_type *e)
{
	struct elevator_queue *eq;
	int i;

	eq = kmalloc_node(sizeof(*eq), GFP_KERNEL | __GFP_ZERO, q->node);
	if (unlikely(!eq))
		goto err;

	eq->ops = &e->ops;
	eq->elevator_type = e;
	kobject_init(&eq->kobj, &elv_ktype);
	mutex_init(&eq->sysfs_lock);

	eq->hash = kmalloc_node(sizeof(struct hlist_head) * ELV_HASH_ENTRIES,
					GFP_KERNEL, q->node);
	if (!eq->hash)
		goto err;

	for (i = 0; i < ELV_HASH_ENTRIES; i++)
		INIT_HLIST_HEAD(&eq->hash[i]);

	return eq;
err:
	kfree(eq);
	elevator_put(e);
	return NULL;
}
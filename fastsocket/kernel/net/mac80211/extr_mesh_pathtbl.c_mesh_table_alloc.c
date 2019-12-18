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
struct mesh_table {int size_order; int hash_mask; int /*<<< orphan*/  gates_lock; int /*<<< orphan*/ * hashwlock; int /*<<< orphan*/  hash_rnd; int /*<<< orphan*/  entries; struct mesh_table* hash_buckets; } ;
struct hlist_head {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct mesh_table*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct mesh_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mesh_table *mesh_table_alloc(int size_order)
{
	int i;
	struct mesh_table *newtbl;

	newtbl = kmalloc(sizeof(struct mesh_table), GFP_ATOMIC);
	if (!newtbl)
		return NULL;

	newtbl->hash_buckets = kzalloc(sizeof(struct hlist_head) *
			(1 << size_order), GFP_ATOMIC);

	if (!newtbl->hash_buckets) {
		kfree(newtbl);
		return NULL;
	}

	newtbl->hashwlock = kmalloc(sizeof(spinlock_t) *
			(1 << size_order), GFP_ATOMIC);
	if (!newtbl->hashwlock) {
		kfree(newtbl->hash_buckets);
		kfree(newtbl);
		return NULL;
	}

	newtbl->size_order = size_order;
	newtbl->hash_mask = (1 << size_order) - 1;
	atomic_set(&newtbl->entries,  0);
	get_random_bytes(&newtbl->hash_rnd,
			sizeof(newtbl->hash_rnd));
	for (i = 0; i <= newtbl->hash_mask; i++)
		spin_lock_init(&newtbl->hashwlock[i]);
	spin_lock_init(&newtbl->gates_lock);

	return newtbl;
}
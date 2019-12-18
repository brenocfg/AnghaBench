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
struct dst_node {int /*<<< orphan*/  node_entry; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int dst_hash (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dst_hash_lock ; 
 int /*<<< orphan*/ * dst_hashtable ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dst_node_add(struct dst_node *n)
{
	unsigned hash = dst_hash(n->name, sizeof(n->name));

	mutex_lock(&dst_hash_lock);
	list_add_tail(&n->node_entry, &dst_hashtable[hash]);
	mutex_unlock(&dst_hash_lock);
}
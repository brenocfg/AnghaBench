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
struct dst_node {int /*<<< orphan*/  node_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_hash_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dst_node_remove(struct dst_node *n)
{
	mutex_lock(&dst_hash_lock);
	list_del_init(&n->node_entry);
	mutex_unlock(&dst_hash_lock);
}
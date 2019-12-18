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
struct pernet_operations {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_generic_ids ; 
 int /*<<< orphan*/  net_mutex ; 
 int /*<<< orphan*/  unregister_pernet_operations (struct pernet_operations*) ; 

void unregister_pernet_gen_subsys(int id, struct pernet_operations *ops)
{
	mutex_lock(&net_mutex);
	unregister_pernet_operations(ops);
	ida_remove(&net_generic_ids, id);
	mutex_unlock(&net_mutex);
}
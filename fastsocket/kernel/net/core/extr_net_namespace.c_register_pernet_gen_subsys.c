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
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  first_device ; 
 int ida_get_new_above (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  ida_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_generic_ids ; 
 int /*<<< orphan*/  net_mutex ; 
 int register_pernet_operations (int /*<<< orphan*/ ,struct pernet_operations*) ; 

int register_pernet_gen_subsys(int *id, struct pernet_operations *ops)
{
	int rv;

	mutex_lock(&net_mutex);
again:
	rv = ida_get_new_above(&net_generic_ids, 1, id);
	if (rv < 0) {
		if (rv == -EAGAIN) {
			ida_pre_get(&net_generic_ids, GFP_KERNEL);
			goto again;
		}
		goto out;
	}
	rv = register_pernet_operations(first_device, ops);
	if (rv < 0)
		ida_remove(&net_generic_ids, *id);
out:
	mutex_unlock(&net_mutex);
	return rv;
}
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
struct nf_ct_ext_type {size_t id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_ext_type_mutex ; 
 int /*<<< orphan*/ * nf_ct_ext_types ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  update_alloc_size (struct nf_ct_ext_type*) ; 

void nf_ct_extend_unregister(struct nf_ct_ext_type *type)
{
	mutex_lock(&nf_ct_ext_type_mutex);
	rcu_assign_pointer(nf_ct_ext_types[type->id], NULL);
	update_alloc_size(type);
	mutex_unlock(&nf_ct_ext_type_mutex);
	rcu_barrier(); /* Wait for completion of call_rcu()'s */
}
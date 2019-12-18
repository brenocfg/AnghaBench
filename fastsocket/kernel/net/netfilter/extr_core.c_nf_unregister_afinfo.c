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
struct nf_afinfo {size_t family; } ;

/* Variables and functions */
 int /*<<< orphan*/  afinfo_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nf_afinfo ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void nf_unregister_afinfo(const struct nf_afinfo *afinfo)
{
	mutex_lock(&afinfo_mutex);
	rcu_assign_pointer(nf_afinfo[afinfo->family], NULL);
	mutex_unlock(&afinfo_mutex);
	synchronize_rcu();
}
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
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nf_afinfo ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nf_afinfo const*) ; 

int nf_register_afinfo(const struct nf_afinfo *afinfo)
{
	int err;

	err = mutex_lock_interruptible(&afinfo_mutex);
	if (err < 0)
		return err;
	rcu_assign_pointer(nf_afinfo[afinfo->family], afinfo);
	mutex_unlock(&afinfo_mutex);
	return 0;
}
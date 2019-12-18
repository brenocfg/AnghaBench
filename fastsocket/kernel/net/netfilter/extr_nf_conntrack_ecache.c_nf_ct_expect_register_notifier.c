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
struct nf_exp_event_notifier {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_ecache_mutex ; 
 int /*<<< orphan*/  nf_expect_event_cb ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nf_exp_event_notifier*) ; 
 struct nf_exp_event_notifier* rcu_dereference (int /*<<< orphan*/ ) ; 

int nf_ct_expect_register_notifier(struct nf_exp_event_notifier *new)
{
	int ret = 0;
	struct nf_exp_event_notifier *notify;

	mutex_lock(&nf_ct_ecache_mutex);
	notify = rcu_dereference(nf_expect_event_cb);
	if (notify != NULL) {
		ret = -EBUSY;
		goto out_unlock;
	}
	rcu_assign_pointer(nf_expect_event_cb, new);
	mutex_unlock(&nf_ct_ecache_mutex);
	return ret;

out_unlock:
	mutex_unlock(&nf_ct_ecache_mutex);
	return ret;
}
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
struct exec_domain {struct exec_domain* next; } ;

/* Variables and functions */
 int EINVAL ; 
 struct exec_domain* exec_domains ; 
 int /*<<< orphan*/  exec_domains_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int
unregister_exec_domain(struct exec_domain *ep)
{
	struct exec_domain	**epp;

	epp = &exec_domains;
	write_lock(&exec_domains_lock);
	for (epp = &exec_domains; *epp; epp = &(*epp)->next) {
		if (ep == *epp)
			goto unregister;
	}
	write_unlock(&exec_domains_lock);
	return -EINVAL;

unregister:
	*epp = ep->next;
	ep->next = NULL;
	write_unlock(&exec_domains_lock);
	return 0;
}
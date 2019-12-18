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
struct uts_namespace {int /*<<< orphan*/  name; int /*<<< orphan*/  proc_inum; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct uts_namespace* ERR_PTR (int) ; 
 struct uts_namespace* create_uts_ns () ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct uts_namespace*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int proc_alloc_inum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uts_sem ; 

__attribute__((used)) static struct uts_namespace *clone_uts_ns(struct uts_namespace *old_ns)
{
	struct uts_namespace *ns;
	int err;

	ns = create_uts_ns();
	if (!ns)
		return ERR_PTR(-ENOMEM);

	err = proc_alloc_inum(&ns->proc_inum);
	if (err) {
		kfree(ns);
		return ERR_PTR(err);
	}

	down_read(&uts_sem);
	memcpy(&ns->name, &old_ns->name, sizeof(ns->name));
	up_read(&uts_sem);
	return ns;
}
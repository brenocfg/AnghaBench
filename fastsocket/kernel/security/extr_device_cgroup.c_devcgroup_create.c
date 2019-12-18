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
struct cgroup_subsys_state {int dummy; } ;
struct dev_cgroup {struct cgroup_subsys_state css; int /*<<< orphan*/  behavior; int /*<<< orphan*/  exceptions; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup {struct cgroup* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCG_DEFAULT_ALLOW ; 
 int ENOMEM ; 
 struct cgroup_subsys_state* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct dev_cgroup* cgroup_to_devcgroup (struct cgroup*) ; 
 int dev_exceptions_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devcgroup_mutex ; 
 int /*<<< orphan*/  kfree (struct dev_cgroup*) ; 
 struct dev_cgroup* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cgroup_subsys_state *devcgroup_create(struct cgroup_subsys *ss,
						struct cgroup *cgroup)
{
	struct dev_cgroup *dev_cgroup, *parent_dev_cgroup;
	struct cgroup *parent_cgroup;
	int ret;

	dev_cgroup = kzalloc(sizeof(*dev_cgroup), GFP_KERNEL);
	if (!dev_cgroup)
		return ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&dev_cgroup->exceptions);
	parent_cgroup = cgroup->parent;

	if (parent_cgroup == NULL)
		dev_cgroup->behavior = DEVCG_DEFAULT_ALLOW;
	else {
		parent_dev_cgroup = cgroup_to_devcgroup(parent_cgroup);
		mutex_lock(&devcgroup_mutex);
		ret = dev_exceptions_copy(&dev_cgroup->exceptions,
					  &parent_dev_cgroup->exceptions);
		dev_cgroup->behavior = parent_dev_cgroup->behavior;
		mutex_unlock(&devcgroup_mutex);
		if (ret) {
			kfree(dev_cgroup);
			return ERR_PTR(ret);
		}
	}

	return &dev_cgroup->css;
}
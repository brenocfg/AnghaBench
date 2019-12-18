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
struct freezer {int state; int /*<<< orphan*/  lock; } ;
struct cgroup {int dummy; } ;
typedef  enum freezer_state { ____Placeholder_freezer_state } freezer_state ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CGROUP_FROZEN 129 
#define  CGROUP_THAWED 128 
 struct freezer* cgroup_freezer (struct cgroup*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int try_to_freeze_cgroup (struct cgroup*,struct freezer*) ; 
 int /*<<< orphan*/  unfreeze_cgroup (struct cgroup*,struct freezer*) ; 
 int /*<<< orphan*/  update_if_frozen (struct cgroup*,struct freezer*) ; 

__attribute__((used)) static int freezer_change_state(struct cgroup *cgroup,
				enum freezer_state goal_state)
{
	struct freezer *freezer;
	int retval = 0;

	freezer = cgroup_freezer(cgroup);

	spin_lock_irq(&freezer->lock);

	update_if_frozen(cgroup, freezer);
	if (goal_state == freezer->state)
		goto out;

	switch (goal_state) {
	case CGROUP_THAWED:
		unfreeze_cgroup(cgroup, freezer);
		break;
	case CGROUP_FROZEN:
		retval = try_to_freeze_cgroup(cgroup, freezer);
		break;
	default:
		BUG();
	}
out:
	spin_unlock_irq(&freezer->lock);

	return retval;
}
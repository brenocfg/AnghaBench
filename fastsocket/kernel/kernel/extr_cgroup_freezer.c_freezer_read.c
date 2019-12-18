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
struct seq_file {int dummy; } ;
struct freezer {int state; int /*<<< orphan*/  lock; } ;
struct cgroup {int dummy; } ;
struct cftype {int dummy; } ;
typedef  enum freezer_state { ____Placeholder_freezer_state } freezer_state ;

/* Variables and functions */
 int CGROUP_FREEZING ; 
 int ENODEV ; 
 struct freezer* cgroup_freezer (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_lock_live_group (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_unlock () ; 
 int /*<<< orphan*/ * freezer_state_strs ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_if_frozen (struct cgroup*,struct freezer*) ; 

__attribute__((used)) static int freezer_read(struct cgroup *cgroup, struct cftype *cft,
			struct seq_file *m)
{
	struct freezer *freezer;
	enum freezer_state state;

	if (!cgroup_lock_live_group(cgroup))
		return -ENODEV;

	freezer = cgroup_freezer(cgroup);
	spin_lock_irq(&freezer->lock);
	state = freezer->state;
	if (state == CGROUP_FREEZING) {
		/* We change from FREEZING to FROZEN lazily if the cgroup was
		 * only partially frozen when we exitted write. */
		update_if_frozen(cgroup, freezer);
		state = freezer->state;
	}
	spin_unlock_irq(&freezer->lock);
	cgroup_unlock();

	seq_puts(m, freezer_state_strs[state]);
	seq_putc(m, '\n');
	return 0;
}
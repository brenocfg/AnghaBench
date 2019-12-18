#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mirror_set {int leg_failure; int /*<<< orphan*/  trigger_event; int /*<<< orphan*/  in_sync; } ;
struct mirror {TYPE_1__* dev; int /*<<< orphan*/  error_type; int /*<<< orphan*/  error_count; struct mirror_set* ms; } ;
typedef  enum dm_raid1_error { ____Placeholder_dm_raid1_error } dm_raid1_error ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMWARN (char*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errors_handled (struct mirror_set*) ; 
 struct mirror* get_default_mirror (struct mirror_set*) ; 
 struct mirror* get_valid_mirror (struct mirror_set*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_default_mirror (struct mirror*) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fail_mirror(struct mirror *m, enum dm_raid1_error error_type)
{
	struct mirror_set *ms = m->ms;
	struct mirror *new;

	ms->leg_failure = 1;

	/*
	 * error_count is used for nothing more than a
	 * simple way to tell if a device has encountered
	 * errors.
	 */
	atomic_inc(&m->error_count);

	if (test_and_set_bit(error_type, &m->error_type))
		return;

	if (!errors_handled(ms))
		return;

	if (m != get_default_mirror(ms))
		goto out;

	if (!ms->in_sync) {
		/*
		 * Better to issue requests to same failing device
		 * than to risk returning corrupt data.
		 */
		DMERR("Primary mirror (%s) failed while out-of-sync: "
		      "Reads may fail.", m->dev->name);
		goto out;
	}

	new = get_valid_mirror(ms);
	if (new)
		set_default_mirror(new);
	else
		DMWARN("All sides of mirror have failed.");

out:
	schedule_work(&ms->trigger_event);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* dev; } ;
struct pgpath {TYPE_5__ path; int /*<<< orphan*/  fail_count; scalar_t__ is_active; TYPE_2__* pg; } ;
struct multipath {int /*<<< orphan*/  lock; int /*<<< orphan*/  trigger_event; int /*<<< orphan*/  nr_valid_paths; int /*<<< orphan*/  ti; struct pgpath* current_pgpath; } ;
struct TYPE_9__ {TYPE_1__* type; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_4__ ps; struct multipath* m; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fail_path ) (TYPE_4__*,TYPE_5__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DM_UEVENT_PATH_FAILED ; 
 int /*<<< orphan*/  dm_path_uevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static int fail_path(struct pgpath *pgpath)
{
	unsigned long flags;
	struct multipath *m = pgpath->pg->m;

	spin_lock_irqsave(&m->lock, flags);

	if (!pgpath->is_active)
		goto out;

	DMWARN("Failing path %s.", pgpath->path.dev->name);

	pgpath->pg->ps.type->fail_path(&pgpath->pg->ps, &pgpath->path);
	pgpath->is_active = 0;
	pgpath->fail_count++;

	m->nr_valid_paths--;

	if (pgpath == m->current_pgpath)
		m->current_pgpath = NULL;

	dm_path_uevent(DM_UEVENT_PATH_FAILED, m->ti,
		      pgpath->path.dev->name, m->nr_valid_paths);

	schedule_work(&m->trigger_event);

out:
	spin_unlock_irqrestore(&m->lock, flags);

	return 0;
}
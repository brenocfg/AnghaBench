#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  work; } ;
struct pgpath {int is_active; TYPE_6__ path; TYPE_3__ activate_path; TYPE_2__* pg; } ;
struct multipath {int /*<<< orphan*/  lock; int /*<<< orphan*/  trigger_event; int /*<<< orphan*/  nr_valid_paths; int /*<<< orphan*/  ti; int /*<<< orphan*/  pg_init_in_progress; TYPE_2__* current_pg; scalar_t__ hw_handler_name; int /*<<< orphan*/  process_queued_ios; int /*<<< orphan*/ * current_pgpath; scalar_t__ queue_size; } ;
struct TYPE_11__ {TYPE_1__* type; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_5__ ps; struct multipath* m; } ;
struct TYPE_7__ {int (* reinstate_path ) (TYPE_5__*,TYPE_6__*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DM_UEVENT_PATH_REINSTATED ; 
 int EINVAL ; 
 int /*<<< orphan*/  dm_path_uevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmpath_handlerd ; 
 int /*<<< orphan*/  kmultipathd ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (TYPE_5__*,TYPE_6__*) ; 

__attribute__((used)) static int reinstate_path(struct pgpath *pgpath)
{
	int r = 0;
	unsigned long flags;
	struct multipath *m = pgpath->pg->m;

	spin_lock_irqsave(&m->lock, flags);

	if (pgpath->is_active)
		goto out;

	if (!pgpath->pg->ps.type->reinstate_path) {
		DMWARN("Reinstate path not supported by path selector %s",
		       pgpath->pg->ps.type->name);
		r = -EINVAL;
		goto out;
	}

	r = pgpath->pg->ps.type->reinstate_path(&pgpath->pg->ps, &pgpath->path);
	if (r)
		goto out;

	pgpath->is_active = 1;

	if (!m->nr_valid_paths++ && m->queue_size) {
		m->current_pgpath = NULL;
		queue_work(kmultipathd, &m->process_queued_ios);
	} else if (m->hw_handler_name && (m->current_pg == pgpath->pg)) {
		if (queue_work(kmpath_handlerd, &pgpath->activate_path.work))
			m->pg_init_in_progress++;
	}

	dm_path_uevent(DM_UEVENT_PATH_REINSTATED, m->ti,
		      pgpath->path.dev->name, m->nr_valid_paths);

	schedule_work(&m->trigger_event);

out:
	spin_unlock_irqrestore(&m->lock, flags);

	return r;
}
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
struct priority_group {scalar_t__ bypassed; struct multipath* m; } ;
struct pgpath {struct priority_group* pg; } ;
struct multipath {unsigned int pg_init_delay_retry; int /*<<< orphan*/  lock; int /*<<< orphan*/  pg_init_wait; int /*<<< orphan*/  process_queued_ios; scalar_t__ queue_io; int /*<<< orphan*/  pg_init_required; scalar_t__ pg_init_in_progress; int /*<<< orphan*/ * current_pg; struct pgpath* current_pgpath; int /*<<< orphan*/  hw_handler_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int,...) ; 
#define  SCSI_DH_DEV_TEMP_BUSY 133 
#define  SCSI_DH_IMM_RETRY 132 
#define  SCSI_DH_NOSYS 131 
#define  SCSI_DH_OK 130 
#define  SCSI_DH_RES_TEMP_UNAVAIL 129 
#define  SCSI_DH_RETRY 128 
 int /*<<< orphan*/  bypass_pg (struct multipath*,struct priority_group*,int) ; 
 int /*<<< orphan*/  fail_path (struct pgpath*) ; 
 int /*<<< orphan*/  kmultipathd ; 
 int /*<<< orphan*/  pg_init_limit_reached (struct multipath*,struct pgpath*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pg_init_done(void *data, int errors)
{
	struct pgpath *pgpath = data;
	struct priority_group *pg = pgpath->pg;
	struct multipath *m = pg->m;
	unsigned long flags;
	unsigned delay_retry = 0;

	/* device or driver problems */
	switch (errors) {
	case SCSI_DH_OK:
		break;
	case SCSI_DH_NOSYS:
		if (!m->hw_handler_name) {
			errors = 0;
			break;
		}
		DMERR("Could not failover the device: Handler scsi_dh_%s "
		      "Error %d.", m->hw_handler_name, errors);
		/*
		 * Fail path for now, so we do not ping pong
		 */
		fail_path(pgpath);
		break;
	case SCSI_DH_DEV_TEMP_BUSY:
		/*
		 * Probably doing something like FW upgrade on the
		 * controller so try the other pg.
		 */
		bypass_pg(m, pg, 1);
		break;
	case SCSI_DH_RETRY:
		/* Wait before retrying. */
		delay_retry = 1;
	case SCSI_DH_IMM_RETRY:
	case SCSI_DH_RES_TEMP_UNAVAIL:
		if (pg_init_limit_reached(m, pgpath))
			fail_path(pgpath);
		errors = 0;
		break;
	default:
		/*
		 * We probably do not want to fail the path for a device
		 * error, but this is what the old dm did. In future
		 * patches we can do more advanced handling.
		 */
		fail_path(pgpath);
	}

	spin_lock_irqsave(&m->lock, flags);
	if (errors) {
		if (pgpath == m->current_pgpath) {
			DMERR("Could not failover device. Error %d.", errors);
			m->current_pgpath = NULL;
			m->current_pg = NULL;
		}
	} else if (!m->pg_init_required)
		pg->bypassed = 0;

	if (--m->pg_init_in_progress)
		/* Activations of other paths are still on going */
		goto out;

	if (!m->pg_init_required)
		m->queue_io = 0;

	m->pg_init_delay_retry = delay_retry;
	queue_work(kmultipathd, &m->process_queued_ios);

	/*
	 * Wake up any thread waiting to suspend.
	 */
	wake_up(&m->pg_init_wait);

out:
	spin_unlock_irqrestore(&m->lock, flags);
}
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
struct request {int /*<<< orphan*/  errors; } ;
struct multipath {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue_if_no_path; int /*<<< orphan*/  nr_valid_paths; } ;
struct dm_mpath_io {scalar_t__ pgpath; } ;

/* Variables and functions */
 int DM_ENDIO_REQUEUE ; 
 int EBADE ; 
 int EILSEQ ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  __must_push_back (struct multipath*) ; 
 int /*<<< orphan*/  fail_path (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int do_end_io(struct multipath *m, struct request *clone,
		     int error, struct dm_mpath_io *mpio)
{
	/*
	 * We don't queue any clone request inside the multipath target
	 * during end I/O handling, since those clone requests don't have
	 * bio clones.  If we queue them inside the multipath target,
	 * we need to make bio clones, that requires memory allocation.
	 * (See drivers/md/dm.c:end_clone_bio() about why the clone requests
	 *  don't have bio clones.)
	 * Instead of queueing the clone request here, we queue the original
	 * request into dm core, which will remake a clone request and
	 * clone bios for it and resubmit it later.
	 */
	int r = DM_ENDIO_REQUEUE;
	unsigned long flags;

	if (!error && !clone->errors)
		return 0;	/* I/O complete */

	if (error == -EOPNOTSUPP || error == -EREMOTEIO || error == -EILSEQ)
		return error;

	if (mpio->pgpath)
		fail_path(mpio->pgpath);

	spin_lock_irqsave(&m->lock, flags);
	if (!m->nr_valid_paths) {
		if (!m->queue_if_no_path) {
			if (!__must_push_back(m))
				r = -EIO;
		} else {
			if (error == -EBADE)
				r = error;
		}
	}
	spin_unlock_irqrestore(&m->lock, flags);

	return r;
}
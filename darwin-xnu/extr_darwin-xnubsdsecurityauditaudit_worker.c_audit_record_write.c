#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ u_quad_t ;
struct vnode {TYPE_1__* v_mount; } ;
struct vfsstatfs {int f_bfree; int f_blocks; unsigned long f_bsize; } ;
struct vfs_context {int dummy; } ;
struct timeval {int dummy; } ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {scalar_t__ af_filesz; scalar_t__ af_currsz; } ;
struct TYPE_5__ {int aq_minfree; } ;
struct TYPE_4__ {struct vfsstatfs mnt_vfsstat; } ;

/* Variables and functions */
 int AUDIT_HARD_LIMIT_FREE_BLOCKS ; 
 int /*<<< orphan*/  AUDIT_TRIGGER_LOW_SPACE ; 
 int /*<<< orphan*/  AUDIT_TRIGGER_NO_SPACE ; 
 int /*<<< orphan*/  AUDIT_TRIGGER_ROTATE_KERNEL ; 
 int /*<<< orphan*/  AUDIT_WORKER_SX_ASSERT () ; 
 int ENOSPC ; 
 int IO_APPEND ; 
 int IO_UNIT ; 
 int MAX_AUDIT_RECORD_SIZE ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  VFS_KERNEL_EVENT ; 
 int /*<<< orphan*/  VNOP_FSYNC (struct vnode*,int /*<<< orphan*/ ,struct vfs_context*) ; 
 scalar_t__ audit_fail_stop ; 
 int audit_file_rotate_wait ; 
 TYPE_3__ audit_fstat ; 
 int audit_in_failure ; 
 scalar_t__ audit_panic_on_write_fail ; 
 int audit_pre_q_len ; 
 int audit_q_len ; 
 TYPE_2__ audit_qctrl ; 
 int /*<<< orphan*/  audit_send_trigger (int /*<<< orphan*/ ) ; 
 int audit_suspended ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ ppsratecheck (struct timeval*,int*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vfs_context_proc (struct vfs_context*) ; 
 int /*<<< orphan*/  vfs_context_ucred (struct vfs_context*) ; 
 int vfs_update_vfsstat (TYPE_1__*,struct vfs_context*,int /*<<< orphan*/ ) ; 
 int vn_rdwr (int /*<<< orphan*/ ,struct vnode*,void*,size_t,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_getwithref (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int vnode_size (struct vnode*,scalar_t__*,struct vfs_context*) ; 

__attribute__((used)) static void
audit_record_write(struct vnode *vp, struct vfs_context *ctx, void *data,
    size_t len)
{
	static struct timeval last_lowspace_trigger;
	static struct timeval last_fail;
	static int cur_lowspace_trigger;
	struct vfsstatfs *mnt_stat;
	int error;
	static int cur_fail;
	uint64_t temp;
	off_t file_size;

	AUDIT_WORKER_SX_ASSERT();	/* audit_file_rotate_wait. */

	if (vp == NULL)
		return;

	if (vnode_getwithref(vp))
		return /*(ENOENT)*/;

	mnt_stat = &vp->v_mount->mnt_vfsstat;

	/*
	 * First, gather statistics on the audit log file and file system so
	 * that we know how we're doing on space.  Consider failure of these
	 * operations to indicate a future inability to write to the file.
	 */
	error = vfs_update_vfsstat(vp->v_mount, ctx, VFS_KERNEL_EVENT);
	if (error)
		goto fail;
	error = vnode_size(vp, &file_size, ctx);
	if (error)
		goto fail;
	audit_fstat.af_currsz = (u_quad_t)file_size;

	/*
	 * We handle four different space-related limits:
	 *
	 * - A fixed (hard) limit on the minimum free blocks we require on
	 *   the file system, and results in record loss, a trigger, and
	 *   possible fail stop due to violating invariants.
	 *
	 * - An administrative (soft) limit, which when fallen below, results
	 *   in the kernel notifying the audit daemon of low space.
	 *
	 * - An audit trail size limit, which when gone above, results in the
	 *   kernel notifying the audit daemon that rotation is desired.
	 *
	 * - The total depth of the kernel audit record exceeding free space,
	 *   which can lead to possible fail stop (with drain), in order to
	 *   prevent violating invariants.  Failure here doesn't halt
	 *   immediately, but prevents new records from being generated.
	 *
	 * Possibly, the last of these should be handled differently, always
	 * allowing a full queue to be lost, rather than trying to prevent
	 * loss.
	 *
	 * First, handle the hard limit, which generates a trigger and may
	 * fail stop.  This is handled in the same manner as ENOSPC from
	 * VOP_WRITE, and results in record loss.
	 */
	if (mnt_stat->f_bfree < AUDIT_HARD_LIMIT_FREE_BLOCKS) {
		error = ENOSPC;
		goto fail_enospc;
	}

	/*
	 * Second, handle falling below the soft limit, if defined; we send
	 * the daemon a trigger and continue processing the record.  Triggers
	 * are limited to 1/sec.
	 */
	if (audit_qctrl.aq_minfree != 0) {
		temp = mnt_stat->f_blocks / (100 / audit_qctrl.aq_minfree);
		if (mnt_stat->f_bfree < temp &&
		    ppsratecheck(&last_lowspace_trigger,
		    &cur_lowspace_trigger, 1))
				(void)audit_send_trigger(
				    AUDIT_TRIGGER_LOW_SPACE);
	}

	/*
	 * If the current file is getting full, generate a rotation trigger
	 * to the daemon.  This is only approximate, which is fine as more
	 * records may be generated before the daemon rotates the file.
	 */
	if ((audit_fstat.af_filesz != 0) && (audit_file_rotate_wait == 0) &&
	    ((u_quad_t)file_size >= audit_fstat.af_filesz)) {
		AUDIT_WORKER_SX_ASSERT();

		audit_file_rotate_wait = 1;
		(void)audit_send_trigger(AUDIT_TRIGGER_ROTATE_KERNEL);
	}

	/*
	 * If the estimated amount of audit data in the audit event queue
	 * (plus records allocated but not yet queued) has reached the amount
	 * of free space on the disk, then we need to go into an audit fail
	 * stop state, in which we do not permit the allocation/committing of
	 * any new audit records.  We continue to process records but don't
	 * allow any activities that might generate new records.  In the
	 * future, we might want to detect when space is available again and
	 * allow operation to continue, but this behavior is sufficient to
	 * meet fail stop requirements in CAPP.
	 */
	if (audit_fail_stop) {
		if ((unsigned long)((audit_q_len + audit_pre_q_len + 1) *
		    MAX_AUDIT_RECORD_SIZE) / mnt_stat->f_bsize >=
		    (unsigned long)(mnt_stat->f_bfree)) {
			if (ppsratecheck(&last_fail, &cur_fail, 1))
				printf("audit_record_write: free space "
				    "below size of audit queue, failing "
				    "stop\n");
			audit_in_failure = 1;
		} else if (audit_in_failure) {
			/*
			 * Note: if we want to handle recovery, this is the
			 * spot to do it: unset audit_in_failure, and issue a
			 * wakeup on the cv.
			 */
		}
	}

	error = vn_rdwr(UIO_WRITE, vp, data, len, (off_t)0, UIO_SYSSPACE,
	    IO_APPEND|IO_UNIT, vfs_context_ucred(ctx), NULL,
	    vfs_context_proc(ctx));
	if (error == ENOSPC)
		goto fail_enospc;
	else if (error)
		goto fail;

	/*
	 * Catch completion of a queue drain here; if we're draining and the
	 * queue is now empty, fail stop.  That audit_fail_stop is implicitly
	 * true, since audit_in_failure can only be set of audit_fail_stop is
	 * set.
	 *
	 * Note: if we handle recovery from audit_in_failure, then we need to
	 * make panic here conditional.
	 */
	if (audit_in_failure) {
		if (audit_q_len == 0 && audit_pre_q_len == 0) {
			(void)VNOP_FSYNC(vp, MNT_WAIT, ctx);
			panic("Audit store overflow; record queue drained.");
		}
	}

	vnode_put(vp);
	return;

fail_enospc:
	/*
	 * ENOSPC is considered a special case with respect to failures, as
	 * this can reflect either our preemptive detection of insufficient
	 * space, or ENOSPC returned by the vnode write call.
	 */
	if (audit_fail_stop) {
		(void)VNOP_FSYNC(vp, MNT_WAIT, ctx);
		panic("Audit log space exhausted and fail-stop set.");
	}
	(void)audit_send_trigger(AUDIT_TRIGGER_NO_SPACE);
	audit_suspended = 1;

	/* FALLTHROUGH */
fail:
	/*
	 * We have failed to write to the file, so the current record is
	 * lost, which may require an immediate system halt.
	 */
	if (audit_panic_on_write_fail) {
		(void)VNOP_FSYNC(vp, MNT_WAIT, ctx);
		panic("audit_worker: write error %d\n", error);
	} else if (ppsratecheck(&last_fail, &cur_fail, 1))
		printf("audit_worker: write error %d\n", error);
	vnode_put(vp);
}
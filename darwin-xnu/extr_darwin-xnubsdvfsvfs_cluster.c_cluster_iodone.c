#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  TYPE_1__* upl_t ;
struct clios {int io_error; int io_completed; scalar_t__ io_wanted; int /*<<< orphan*/  io_mtxp; } ;
typedef  TYPE_1__* caddr_t ;
typedef  TYPE_1__* buf_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_19__ {int b_lblkno; int b_bcount; int b_flags; int b_uploffset; int b_validend; int b_error; int b_resid; scalar_t__ b_cliodone; struct TYPE_19__* b_upl; struct TYPE_19__* b_trans_next; int /*<<< orphan*/  b_dev; scalar_t__ b_iostate; struct TYPE_19__* b_real_bp; int /*<<< orphan*/  b_vp; scalar_t__ b_trans_head; } ;

/* Variables and functions */
 int B_AGE ; 
 int B_COMMIT_UPL ; 
 int B_EOT ; 
 int B_ERROR ; 
 int B_PHYS ; 
 int B_READ ; 
 int B_TDONE ; 
 TYPE_1__* CLUSTER_IO_WAITING ; 
 int /*<<< orphan*/  DBG_FSRW ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int EIO ; 
 scalar_t__ FALSE ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ISSET (int,int) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,TYPE_1__*,...) ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 scalar_t__ TRUE ; 
 int UPL_COMMIT_FREE_ON_EMPTY ; 
 int UPL_COMMIT_INACTIVATE ; 
 int UPL_COMMIT_SET_DIRTY ; 
 int /*<<< orphan*/  __IGNORE_WCASTALIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  buf_biodone (TYPE_1__*) ; 
 int /*<<< orphan*/ * cl_transaction_mtxp ; 
 int /*<<< orphan*/  cluster_handle_associated_upl (struct clios*,TYPE_1__*,int,int) ; 
 int cluster_ioerror (TYPE_1__*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_zero (TYPE_1__*,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  free_io_buf (TYPE_1__*) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  ubc_upl_commit_range (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  upl_set_iodone_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

__attribute__((used)) static int
cluster_iodone(buf_t bp, void *callback_arg)
{
        int	b_flags;
        int	error;
	int	total_size;
	int	total_resid;
	int	upl_offset;
	int	zero_offset;
	int	pg_offset = 0;
        int	commit_size = 0;
        int	upl_flags = 0;
	int	transaction_size = 0;
	upl_t	upl;
	buf_t	cbp;
	buf_t	cbp_head;
	buf_t	cbp_next;
	buf_t	real_bp;
	vnode_t	vp;
	struct	clios *iostate;
	boolean_t	transaction_complete = FALSE;

	__IGNORE_WCASTALIGN(cbp_head = (buf_t)(bp->b_trans_head));

	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 20)) | DBG_FUNC_START,
		     cbp_head, bp->b_lblkno, bp->b_bcount, bp->b_flags, 0);

	if (cbp_head->b_trans_next || !(cbp_head->b_flags & B_EOT)) {
		lck_mtx_lock_spin(cl_transaction_mtxp);

		bp->b_flags |= B_TDONE;

		for (cbp = cbp_head; cbp; cbp = cbp->b_trans_next) {
			/*
			 * all I/O requests that are part of this transaction
			 * have to complete before we can process it
			 */
			if ( !(cbp->b_flags & B_TDONE)) {

				KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 20)) | DBG_FUNC_END,
					     cbp_head, cbp, cbp->b_bcount, cbp->b_flags, 0);

				lck_mtx_unlock(cl_transaction_mtxp);

				return 0;
			}

			if (cbp->b_trans_next == CLUSTER_IO_WAITING) {
				KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 20)) | DBG_FUNC_END,
							 cbp_head, cbp, cbp->b_bcount, cbp->b_flags, 0);

				lck_mtx_unlock(cl_transaction_mtxp);
				wakeup(cbp);

				return 0;
			}

			if (cbp->b_flags & B_EOT)
				transaction_complete = TRUE;
		}
		lck_mtx_unlock(cl_transaction_mtxp);

		if (transaction_complete == FALSE) {
			KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 20)) | DBG_FUNC_END,
				     cbp_head, 0, 0, 0, 0);
			return 0;
		}
	}
	error       = 0;
	total_size  = 0;
	total_resid = 0;

	cbp        = cbp_head;
	vp	   = cbp->b_vp;
	upl_offset = cbp->b_uploffset;
	upl        = cbp->b_upl;
	b_flags    = cbp->b_flags;
	real_bp    = cbp->b_real_bp;
	zero_offset= cbp->b_validend;
	iostate    = (struct clios *)cbp->b_iostate;

	if (real_bp)
	        real_bp->b_dev = cbp->b_dev;

	while (cbp) {
		if ((cbp->b_flags & B_ERROR) && error == 0)
		        error = cbp->b_error;

		total_resid += cbp->b_resid;
		total_size  += cbp->b_bcount;

		cbp_next = cbp->b_trans_next;

		if (cbp_next == NULL)
		        /*
			 * compute the overall size of the transaction
			 * in case we created one that has 'holes' in it
			 * 'total_size' represents the amount of I/O we
			 * did, not the span of the transaction w/r to the UPL
			 */
			transaction_size = cbp->b_uploffset + cbp->b_bcount - upl_offset;

		if (cbp != cbp_head)
		        free_io_buf(cbp);

		cbp = cbp_next;
	}

	if (ISSET(b_flags, B_COMMIT_UPL)) {
		cluster_handle_associated_upl(iostate,
					      cbp_head->b_upl,
					      upl_offset,
					      transaction_size);
	}

	if (error == 0 && total_resid)
		error = EIO;

	if (error == 0) {
	        int	(*cliodone_func)(buf_t, void *) = (int (*)(buf_t, void *))(cbp_head->b_cliodone);

		if (cliodone_func != NULL) {
		        cbp_head->b_bcount = transaction_size;

		        error = (*cliodone_func)(cbp_head, callback_arg);
		}
	}
	if (zero_offset)
	        cluster_zero(upl, zero_offset, PAGE_SIZE - (zero_offset & PAGE_MASK), real_bp);

        free_io_buf(cbp_head);

	if (iostate) {
	        int need_wakeup = 0;

	        /*
		 * someone has issued multiple I/Os asynchrounsly
		 * and is waiting for them to complete (streaming)
		 */
		lck_mtx_lock_spin(&iostate->io_mtxp);

	        if (error && iostate->io_error == 0)
		        iostate->io_error = error;

		iostate->io_completed += total_size;

		if (iostate->io_wanted) {
		        /*
		         * someone is waiting for the state of
			 * this io stream to change
			 */
		        iostate->io_wanted = 0;
			need_wakeup = 1;
		}
		lck_mtx_unlock(&iostate->io_mtxp);

		if (need_wakeup)
		        wakeup((caddr_t)&iostate->io_wanted);
	}

	if (b_flags & B_COMMIT_UPL) {

		pg_offset   = upl_offset & PAGE_MASK;
		commit_size = (pg_offset + transaction_size + (PAGE_SIZE - 1)) & ~PAGE_MASK;

		if (error) {
		        upl_set_iodone_error(upl, error);

			upl_flags = cluster_ioerror(upl, upl_offset - pg_offset, commit_size, error, b_flags, vp);
		} else {
			upl_flags = UPL_COMMIT_FREE_ON_EMPTY;

			if ((b_flags & B_PHYS) && (b_flags & B_READ)) 
			        upl_flags |= UPL_COMMIT_SET_DIRTY;

			if (b_flags & B_AGE)
			        upl_flags |= UPL_COMMIT_INACTIVATE;

			ubc_upl_commit_range(upl, upl_offset - pg_offset, commit_size, upl_flags);
		}
	}
	if (real_bp) {
		if (error) {
			real_bp->b_flags |= B_ERROR;
			real_bp->b_error = error;
		}
		real_bp->b_resid = total_resid;

		buf_biodone(real_bp);
	}
	KERNEL_DEBUG((FSDBG_CODE(DBG_FSRW, 20)) | DBG_FUNC_END,
		     upl, upl_offset - pg_offset, commit_size, (error << 24) | upl_flags, 0);

	return (error);
}
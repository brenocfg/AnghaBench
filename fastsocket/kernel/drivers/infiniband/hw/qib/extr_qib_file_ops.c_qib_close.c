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
struct qib_filedata {int rec_cpu_num; int subctxt; scalar_t__ pq; struct qib_ctxtdata* rcd; } ;
struct qib_devdata {int /*<<< orphan*/  freectxts; scalar_t__ pageshadow; int /*<<< orphan*/  (* f_clear_tids ) (struct qib_devdata*,struct qib_ctxtdata*) ;int /*<<< orphan*/  (* f_rcvctrl ) (int /*<<< orphan*/ ,int,unsigned int) ;scalar_t__ kregbase; int /*<<< orphan*/  uctxt_lock; int /*<<< orphan*/ ** rcd; } ;
struct qib_ctxtdata {int active_slaves; unsigned int ctxt; int /*<<< orphan*/  piocnt; int /*<<< orphan*/  pio_base; int /*<<< orphan*/  ppd; scalar_t__ flag; scalar_t__ pionowait; scalar_t__ rcvnowait; scalar_t__ piowait_to; scalar_t__ rcvwait_to; scalar_t__ pid; scalar_t__* subpid; scalar_t__ cnt; struct qib_devdata* dd; } ;
struct inode {int dummy; } ;
struct file {struct qib_filedata* private_data; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  sps_ctxts; } ;

/* Variables and functions */
 int QIB_RCVCTRL_CTXT_DIS ; 
 int QIB_RCVCTRL_INTRAVAIL_DIS ; 
 int /*<<< orphan*/  TXCHK_CHG_TYPE_KERN ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qib_filedata*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_chg_pioavailkernel (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_clean_part_key (struct qib_ctxtdata*,struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_cpulist ; 
 int /*<<< orphan*/  qib_disarm_piobufs (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_flush_wc () ; 
 int /*<<< orphan*/  qib_free_ctxtdata (struct qib_devdata*,struct qib_ctxtdata*) ; 
 int /*<<< orphan*/  qib_mutex ; 
 TYPE_1__ qib_stats ; 
 int /*<<< orphan*/  qib_user_sdma_queue_destroy (scalar_t__) ; 
 int /*<<< orphan*/  qib_user_sdma_queue_drain (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct qib_devdata*,struct qib_ctxtdata*) ; 
 int /*<<< orphan*/  unlock_expected_tids (struct qib_ctxtdata*) ; 

__attribute__((used)) static int qib_close(struct inode *in, struct file *fp)
{
	int ret = 0;
	struct qib_filedata *fd;
	struct qib_ctxtdata *rcd;
	struct qib_devdata *dd;
	unsigned long flags;
	unsigned ctxt;
	pid_t pid;

	mutex_lock(&qib_mutex);

	fd = fp->private_data;
	fp->private_data = NULL;
	rcd = fd->rcd;
	if (!rcd) {
		mutex_unlock(&qib_mutex);
		goto bail;
	}

	dd = rcd->dd;

	/* ensure all pio buffer writes in progress are flushed */
	qib_flush_wc();

	/* drain user sdma queue */
	if (fd->pq) {
		qib_user_sdma_queue_drain(rcd->ppd, fd->pq);
		qib_user_sdma_queue_destroy(fd->pq);
	}

	if (fd->rec_cpu_num != -1)
		__clear_bit(fd->rec_cpu_num, qib_cpulist);

	if (--rcd->cnt) {
		/*
		 * XXX If the master closes the context before the slave(s),
		 * revoke the mmap for the eager receive queue so
		 * the slave(s) don't wait for receive data forever.
		 */
		rcd->active_slaves &= ~(1 << fd->subctxt);
		rcd->subpid[fd->subctxt] = 0;
		mutex_unlock(&qib_mutex);
		goto bail;
	}

	/* early; no interrupt users after this */
	spin_lock_irqsave(&dd->uctxt_lock, flags);
	ctxt = rcd->ctxt;
	dd->rcd[ctxt] = NULL;
	pid = rcd->pid;
	rcd->pid = 0;
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	if (rcd->rcvwait_to || rcd->piowait_to ||
	    rcd->rcvnowait || rcd->pionowait) {
		rcd->rcvwait_to = 0;
		rcd->piowait_to = 0;
		rcd->rcvnowait = 0;
		rcd->pionowait = 0;
	}
	if (rcd->flag)
		rcd->flag = 0;

	if (dd->kregbase) {
		/* atomically clear receive enable ctxt and intr avail. */
		dd->f_rcvctrl(rcd->ppd, QIB_RCVCTRL_CTXT_DIS |
				  QIB_RCVCTRL_INTRAVAIL_DIS, ctxt);

		/* clean up the pkeys for this ctxt user */
		qib_clean_part_key(rcd, dd);
		qib_disarm_piobufs(dd, rcd->pio_base, rcd->piocnt);
		qib_chg_pioavailkernel(dd, rcd->pio_base,
				       rcd->piocnt, TXCHK_CHG_TYPE_KERN, NULL);

		dd->f_clear_tids(dd, rcd);

		if (dd->pageshadow)
			unlock_expected_tids(rcd);
		qib_stats.sps_ctxts--;
		dd->freectxts++;
	}

	mutex_unlock(&qib_mutex);
	qib_free_ctxtdata(dd, rcd); /* after releasing the mutex */

bail:
	kfree(fd);
	return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  TYPE_3__* uthread_t ;
typedef  scalar_t__ uint64_t ;
struct waitq_set {int dummy; } ;
struct waitq {int dummy; } ;
struct tty {int dummy; } ;
struct knote {struct tty* kn_hook; TYPE_2__* kn_fp; } ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_7__ {struct waitq_set* uu_wqset; } ;
struct TYPE_6__ {TYPE_1__* f_fglob; } ;
struct TYPE_5__ {scalar_t__ fg_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTTY ; 
 int FMARK ; 
 scalar_t__ KERN_SUCCESS ; 
 int SYNC_POLICY_FIFO ; 
 int SYNC_POLICY_PREPOST ; 
 int VNOP_SELECT (scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_3__* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int knote_get_seltype (struct knote*) ; 
 int /*<<< orphan*/  knote_set_error (struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct waitq**,scalar_t__*,int) ; 
 struct tty* tty_from_waitq (struct waitq*,int) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttyhold (struct tty*) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  waitq_link_release (scalar_t__) ; 
 scalar_t__ waitq_link_reserve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_set_deinit (struct waitq_set*) ; 
 scalar_t__ waitq_set_init (struct waitq_set*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_set_lazy_init_link (struct waitq_set*) ; 

__attribute__((used)) static int
tty_set_knote_hook(struct knote *kn)
{
	uthread_t uth;
	vfs_context_t ctx;
	vnode_t vp;
	kern_return_t kr;
	struct waitq *wq = NULL;
	struct waitq_set *old_wqs;
	struct waitq_set tmp_wqs;
	uint64_t rsvd, rsvd_arg;
	uint64_t *rlptr = NULL;
	int selres = -1;
	struct tty *tp;

	uth = get_bsdthread_info(current_thread());

	ctx = vfs_context_current();
	vp = (vnode_t)kn->kn_fp->f_fglob->fg_data;

	/*
	 * Reserve a link element to avoid potential allocation under
	 * a spinlock.
	 */
	rsvd = rsvd_arg = waitq_link_reserve(NULL);
	rlptr = (void *)&rsvd_arg;

	/*
	 * Trick selrecord into hooking a known waitq set into the device's selinfo
	 * waitq.  Once the link is in place, we can get back into the selinfo from
	 * the waitq and subsequently the tty (see tty_from_waitq).
	 *
	 * We can't use a real waitq set (such as the kqueue's) because wakeups
	 * might happen before we can unlink it.
	 */
	kr = waitq_set_init(&tmp_wqs, SYNC_POLICY_FIFO | SYNC_POLICY_PREPOST, NULL,
			NULL);
	assert(kr == KERN_SUCCESS);

	/*
	 * Lazy allocate the waitqset to avoid potential allocation under
	 * a spinlock;
	 */
	waitq_set_lazy_init_link(&tmp_wqs);

	old_wqs = uth->uu_wqset;
	uth->uu_wqset = &tmp_wqs;
	/*
	 * FMARK forces selects to always call selrecord, even if data is
	 * available.  See ttselect, ptsselect, ptcselect.
	 *
	 * selres also contains the data currently available in the tty.
	 */
	selres = VNOP_SELECT(vp, knote_get_seltype(kn) | FMARK, 0, rlptr, ctx);
	uth->uu_wqset = old_wqs;

	/*
	 * Make sure to cleanup the reserved link - this guards against
	 * drivers that may not actually call selrecord().
	 */
	waitq_link_release(rsvd);
	if (rsvd == rsvd_arg) {
		/*
		 * The driver didn't call selrecord -- there's no tty hooked up so we
		 * can't attach.
		 */
		knote_set_error(kn, ENOTTY);
		selres = -1;
		goto out;
	}

	/* rlptr may not point to a properly aligned pointer */
	memcpy(&wq, rlptr, sizeof(void *));

	tp = tty_from_waitq(wq, knote_get_seltype(kn));
	assert(tp != NULL);

	/*
	 * Take a reference and stash the tty in the knote.
	 */
	tty_lock(tp);
	ttyhold(tp);
	kn->kn_hook = tp;
	tty_unlock(tp);

out:
	/*
	 * Cleaning up the wqset will unlink its waitq and clean up any preposts
	 * that occurred as a result of data coming in while the tty was attached.
	 */
	waitq_set_deinit(&tmp_wqs);

	return selres;
}
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
typedef  scalar_t__ wait_result_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  thread_t ;
struct waitq {int dummy; } ;
struct _select_data {int* retval; scalar_t__ count; scalar_t__ abstime; struct select_nocancel_args* args; } ;
struct TYPE_2__ {struct _select_data uus_select_data; } ;
struct _select {int /*<<< orphan*/ * obits; int /*<<< orphan*/  ibits; } ;
struct uthread {int uu_flag; scalar_t__ uu_oldmask; scalar_t__ uu_sigmask; int /*<<< orphan*/  uu_wqstate_sz; scalar_t__ uu_wqset; TYPE_1__ uu_save; struct _select uu_select; } ;
struct select_nocancel_args {scalar_t__ ex; scalar_t__ ou; scalar_t__ in; int /*<<< orphan*/  nd; scalar_t__ tv; } ;
struct proc {int p_flag; } ;
typedef  int /*<<< orphan*/  fd_mask ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  NFDBITS ; 
 int /*<<< orphan*/  NO_EVENT64 ; 
 int /*<<< orphan*/  OSBitAndAtomic (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  OSBitOrAtomic (int,int*) ; 
 int PCATCH ; 
 int PSOCK ; 
 int P_SELECT ; 
 int SEL_FIRSTPASS ; 
 int SEL_SECONDPASS ; 
 int /*<<< orphan*/  THREAD_ABORTSAFE ; 
 scalar_t__ THREAD_AWAKENED ; 
 int /*<<< orphan*/  TIMEOUT_NO_LEEWAY ; 
 int /*<<< orphan*/  TIMEOUT_URGENCY_USER_NORMAL ; 
 int UT_SAS_OLDMASK ; 
 int /*<<< orphan*/  bzero (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_get_uptime (scalar_t__*) ; 
 int copyout (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int howmany (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nselcoll ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  selcontinue ; 
 int /*<<< orphan*/  seldrop (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int selscan (struct proc*,struct _select*,struct _select_data*,int /*<<< orphan*/ ,int*,int,scalar_t__) ; 
 int tsleep1 (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waitq_assert_wait64_leeway (struct waitq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_set_deinit (scalar_t__) ; 

int
selprocess(int error, int sel_pass)
{
	int ncoll;
	u_int ni, nw;
	thread_t th_act;
	struct uthread	*uth;
	struct proc *p;
	struct select_nocancel_args *uap;
	int *retval;
	struct _select *sel;
	struct _select_data *seldata;
	int unwind = 1;
	int prepost = 0;
	int somewakeup = 0;
	int doretry = 0;
	wait_result_t wait_result;

	p = current_proc();
	th_act = current_thread();
	uth = get_bsdthread_info(th_act);
	sel = &uth->uu_select;
	seldata = &uth->uu_save.uus_select_data;
	uap = seldata->args;
	retval = seldata->retval;

	if ((error != 0) && (sel_pass == SEL_FIRSTPASS))
		unwind = 0;
	if (seldata->count == 0)
		unwind = 0;
retry:
	if (error != 0)
		goto done;

	ncoll = nselcoll;
	OSBitOrAtomic(P_SELECT, &p->p_flag);

	/* skip scans if the select is just for timeouts */
	if (seldata->count) {
		error = selscan(p, sel, seldata, uap->nd, retval, sel_pass, uth->uu_wqset);
		if (error || *retval) {
			goto done;
		}
		if (prepost || somewakeup) {
			/*
			 * if the select of log, then we can wakeup and
			 * discover some one else already read the data;
			 * go to select again if time permits
			 */
			prepost = 0;
			somewakeup = 0;
			doretry = 1;
		}
	}

	if (uap->tv) {
		uint64_t	now;

		clock_get_uptime(&now);
		if (now >= seldata->abstime)
			goto done;
	}

	if (doretry) {
		/* cleanup obits and try again */
		doretry = 0;
		sel_pass = SEL_FIRSTPASS;
		goto retry;
	}

	/*
	 * To effect a poll, the timeout argument should be
	 * non-nil, pointing to a zero-valued timeval structure.
	 */
	if (uap->tv && seldata->abstime == 0) {
		goto done;
	}

	/* No spurious wakeups due to colls,no need to check for them */
	 if ((sel_pass == SEL_SECONDPASS) || ((p->p_flag & P_SELECT) == 0)) {
		sel_pass = SEL_FIRSTPASS;
		goto retry;
	}

	OSBitAndAtomic(~((uint32_t)P_SELECT), &p->p_flag);

	/* if the select is just for timeout skip check */
	if (seldata->count && (sel_pass == SEL_SECONDPASS))
		panic("selprocess: 2nd pass assertwaiting");

	/* waitq_set has waitqueue as first element */
	wait_result = waitq_assert_wait64_leeway((struct waitq *)uth->uu_wqset,
						 NO_EVENT64, THREAD_ABORTSAFE,
						 TIMEOUT_URGENCY_USER_NORMAL,
						 seldata->abstime,
						 TIMEOUT_NO_LEEWAY);
	if (wait_result != THREAD_AWAKENED) {
		/* there are no preposted events */
		error = tsleep1(NULL, PSOCK | PCATCH,
				"select", 0, selcontinue);
	} else  {
		prepost = 1;
		error = 0;
	}

	if (error == 0) {
		sel_pass = SEL_SECONDPASS;
		if (!prepost)
			somewakeup = 1;
		goto retry;
	}
done:
	if (unwind) {
		seldrop(p, sel->ibits, uap->nd);
		waitq_set_deinit(uth->uu_wqset);
		/*
		 * zero out the waitq pointer array to avoid use-after free
		 * errors in the selcount error path (seldrop_locked) if/when
		 * the thread re-calls select().
		 */
		bzero((void *)uth->uu_wqset, uth->uu_wqstate_sz);
	}
	OSBitAndAtomic(~((uint32_t)P_SELECT), &p->p_flag);
	/* select is not restarted after signals... */
	if (error == ERESTART)
		error = EINTR;
	if (error == EWOULDBLOCK)
		error = 0;
	nw = howmany(uap->nd, NFDBITS);
	ni = nw * sizeof(fd_mask);

#define	putbits(name, x) \
	do { \
		if (uap->name && (error2 = \
			copyout((caddr_t)&sel->obits[(x) * nw], uap->name, ni))) \
			error = error2; \
	} while (0)

	if (error == 0) {
		int error2;

		putbits(in, 0);
		putbits(ou, 1);
		putbits(ex, 2);
#undef putbits
	}

	if (error != EINTR && sel_pass == SEL_SECONDPASS && uth->uu_flag & UT_SAS_OLDMASK) {
		/* restore signal mask - continuation case */
		uth->uu_sigmask = uth->uu_oldmask;
		uth->uu_oldmask = 0;
		uth->uu_flag &= ~UT_SAS_OLDMASK;
	}

	return(error);
}
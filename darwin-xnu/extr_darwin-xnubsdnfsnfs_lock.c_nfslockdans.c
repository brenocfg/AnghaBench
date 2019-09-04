#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct lockd_ans {scalar_t__ la_version; int la_flags; scalar_t__ la_errno; int /*<<< orphan*/  la_len; int /*<<< orphan*/  la_start; int /*<<< orphan*/  la_pid; int /*<<< orphan*/  la_xid; } ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_8__ {int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_start; int /*<<< orphan*/  l_pid; } ;
struct TYPE_9__ {int lm_flags; TYPE_1__ lm_fl; } ;
struct TYPE_10__ {scalar_t__ lmr_errno; int lmr_answered; TYPE_2__ lmr_msg; } ;
typedef  TYPE_3__ LOCKD_MSG_REQUEST ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int LOCKD_ANS_DENIED_GRACE ; 
 int LOCKD_ANS_GRANTED ; 
 int LOCKD_ANS_LOCK_EXCL ; 
 int LOCKD_ANS_LOCK_INFO ; 
 scalar_t__ LOCKD_ANS_VERSION ; 
 int LOCKD_MSG_CANCEL ; 
 int LOCKD_MSG_DENIED_GRACE ; 
 int LOCKD_MSG_TEST ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_lock_mutex ; 
 scalar_t__ nfs_lockdmsg_compare_to_answer (TYPE_3__*,struct lockd_ans*) ; 
 TYPE_3__* nfs_lockdmsg_find_by_answer (struct lockd_ans*) ; 
 TYPE_3__* nfs_lockdmsg_find_by_xid (int /*<<< orphan*/ ) ; 
 int proc_suser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (TYPE_3__*) ; 

int
nfslockdans(proc_t p, struct lockd_ans *ansp)
{
	LOCKD_MSG_REQUEST *msgreq;
	int error;

	/* Let root make this call. */
	error = proc_suser(p);
	if (error)
		return (error);

	/* the version should match, or we're out of sync */
	if (ansp->la_version != LOCKD_ANS_VERSION)
		return (EINVAL);

	lck_mtx_lock(nfs_lock_mutex);

	/* try to find the lockd message by transaction id (cookie) */
	msgreq = nfs_lockdmsg_find_by_xid(ansp->la_xid);
	if (ansp->la_flags & LOCKD_ANS_GRANTED) {
		/*
		 * We can't depend on the granted message having our cookie,
		 * so we check the answer against the lockd message found.
		 * If no message was found or it doesn't match the answer,
		 * we look for the lockd message by the answer's lock info.
		 */
		if (!msgreq || nfs_lockdmsg_compare_to_answer(msgreq, ansp))
			msgreq = nfs_lockdmsg_find_by_answer(ansp);
		/*
		 * We need to make sure this request isn't being cancelled
		 * If it is, we don't want to accept the granted message.
		 */
		if (msgreq && (msgreq->lmr_msg.lm_flags & LOCKD_MSG_CANCEL))
			msgreq = NULL;
	}
	if (!msgreq) {
		lck_mtx_unlock(nfs_lock_mutex);
		return (EPIPE);
	}

	msgreq->lmr_errno = ansp->la_errno;
	if ((msgreq->lmr_msg.lm_flags & LOCKD_MSG_TEST) && msgreq->lmr_errno == 0) {
		if (ansp->la_flags & LOCKD_ANS_LOCK_INFO) {
			if (ansp->la_flags & LOCKD_ANS_LOCK_EXCL)
				msgreq->lmr_msg.lm_fl.l_type = F_WRLCK;
			else
				msgreq->lmr_msg.lm_fl.l_type = F_RDLCK;
			msgreq->lmr_msg.lm_fl.l_pid = ansp->la_pid;
			msgreq->lmr_msg.lm_fl.l_start = ansp->la_start;
			msgreq->lmr_msg.lm_fl.l_len = ansp->la_len;
		} else {
			msgreq->lmr_msg.lm_fl.l_type = F_UNLCK;
		}
	}
	if (ansp->la_flags & LOCKD_ANS_DENIED_GRACE)
		msgreq->lmr_msg.lm_flags |= LOCKD_MSG_DENIED_GRACE;

	msgreq->lmr_answered = 1;
	lck_mtx_unlock(nfs_lock_mutex);
	wakeup(msgreq);

	return (0);
}
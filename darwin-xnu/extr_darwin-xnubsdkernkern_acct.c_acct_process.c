#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct tty {int /*<<< orphan*/  t_dev; } ;
struct timeval {int tv_sec; int tv_usec; } ;
struct session {int dummy; } ;
struct rusage {int ru_ixrss; int ru_idrss; int ru_isrss; int ru_inblock; int ru_oublock; } ;
struct acct {int ac_mem; int /*<<< orphan*/  ac_flag; int /*<<< orphan*/  ac_tty; int /*<<< orphan*/  ac_gid; int /*<<< orphan*/  ac_uid; void* ac_io; void* ac_etime; int /*<<< orphan*/  ac_btime; void* ac_stime; void* ac_utime; int /*<<< orphan*/  ac_comm; } ;
typedef  TYPE_2__* proc_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  an_acct ;
struct TYPE_13__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_12__ {int p_flag; int /*<<< orphan*/  p_acflag; TYPE_1__* p_stats; TYPE_4__ p_start; int /*<<< orphan*/  p_comm; } ;
struct TYPE_11__ {struct rusage p_ru; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCT_SUBSYS_LOCK () ; 
 int /*<<< orphan*/  ACCT_SUBSYS_UNLOCK () ; 
 int IO_APPEND ; 
 int IO_UNIT ; 
 int /*<<< orphan*/  NODEV ; 
 struct vnode* NULLVP ; 
 int P_CONTROLT ; 
 struct session* SESSION_NULL ; 
 struct tty* SESSION_TP (struct session*) ; 
 struct tty* TTY_NULL ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 struct vnode* acctp ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  calcru (TYPE_2__*,struct timeval*,struct timeval*,int /*<<< orphan*/ *) ; 
 void* encode_comp_t (int,int) ; 
 int hz ; 
 int /*<<< orphan*/  kauth_cred_getrgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_getruid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int /*<<< orphan*/  proc_lock (TYPE_2__*) ; 
 struct session* proc_session (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  session_rele (struct session*) ; 
 int tick ; 
 int /*<<< orphan*/  timevaladd (struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,TYPE_4__*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int vn_rdwr (int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,TYPE_2__*) ; 
 int vnode_getwithref (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 

int
acct_process(proc_t p)
{
	struct acct an_acct;
	struct rusage rup, *r;
	struct timeval ut, st, tmp;
	int t;
	int error;
	struct vnode *vp;
	kauth_cred_t safecred;
	struct session * sessp;
	struct  tty *tp;

	/* If accounting isn't enabled, don't bother */
	ACCT_SUBSYS_LOCK();
	vp = acctp;
	if (vp == NULLVP) {
		ACCT_SUBSYS_UNLOCK();
		return (0);
	}

	/*
	 * Get process accounting information.
	 */

	/* (1) The name of the command that ran */
	bcopy(p->p_comm, an_acct.ac_comm, sizeof an_acct.ac_comm);

	/* (2) The amount of user and system time that was used */
	calcru(p, &ut, &st, NULL);
	an_acct.ac_utime = encode_comp_t(ut.tv_sec, ut.tv_usec);
	an_acct.ac_stime = encode_comp_t(st.tv_sec, st.tv_usec);

	/* (3) The elapsed time the commmand ran (and its starting time) */
	an_acct.ac_btime = p->p_start.tv_sec;
	microtime(&tmp);
	timevalsub(&tmp, &p->p_start);
	an_acct.ac_etime = encode_comp_t(tmp.tv_sec, tmp.tv_usec);

	/* (4) The average amount of memory used */
	proc_lock(p);
	rup = p->p_stats->p_ru;
	proc_unlock(p);
	r = &rup;
	tmp = ut;
	timevaladd(&tmp, &st);
	t = tmp.tv_sec * hz + tmp.tv_usec / tick;
	if (t)
		an_acct.ac_mem = (r->ru_ixrss + r->ru_idrss + r->ru_isrss) / t;
	else
		an_acct.ac_mem = 0;

	/* (5) The number of disk I/O operations done */
	an_acct.ac_io = encode_comp_t(r->ru_inblock + r->ru_oublock, 0);

	/* (6) The UID and GID of the process */
	safecred = kauth_cred_proc_ref(p);

	an_acct.ac_uid = kauth_cred_getruid(safecred);
	an_acct.ac_gid = kauth_cred_getrgid(safecred);

	/* (7) The terminal from which the process was started */
	
	sessp = proc_session(p);
	if ((p->p_flag & P_CONTROLT) && (sessp != SESSION_NULL) && ((tp = SESSION_TP(sessp)) != TTY_NULL)) {
		tty_lock(tp);
		an_acct.ac_tty = tp->t_dev;
		tty_unlock(tp);
	 }else
		an_acct.ac_tty = NODEV;

	if (sessp != SESSION_NULL)
		session_rele(sessp);

	/* (8) The boolean flags that tell how the process terminated, etc. */
	an_acct.ac_flag = p->p_acflag;

	/*
	 * Now, just write the accounting information to the file.
	 */
	if ((error = vnode_getwithref(vp)) == 0) {
	        error = vn_rdwr(UIO_WRITE, vp, (caddr_t)&an_acct, sizeof (an_acct),
				(off_t)0, UIO_SYSSPACE, IO_APPEND|IO_UNIT, safecred,
				(int *)0, p);
		vnode_put(vp);
	}

	kauth_cred_unref(&safecred);
	ACCT_SUBSYS_UNLOCK();

	return (error);
}
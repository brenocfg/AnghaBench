#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_char ;
struct winsize {int dummy; } ;
struct uthread {int uu_sigmask; } ;
struct user_termios {int dummy; } ;
struct clist {int /*<<< orphan*/  c_cs; } ;
struct TYPE_16__ {int c_cc; } ;
struct tty {int t_state; int t_line; int (* t_param ) (struct tty*,struct termios*) ;int t_cflag; int t_lflag; int t_timeout; struct winsize t_winsize; struct pgrp* t_pgrp; struct session* t_session; int /*<<< orphan*/  t_dev; int /*<<< orphan*/ * t_cc; int /*<<< orphan*/  t_oflag; int /*<<< orphan*/  t_iflag; struct clist t_canq; struct clist t_rawq; int /*<<< orphan*/  t_ospeed; int /*<<< orphan*/  t_ispeed; TYPE_1__ t_outq; int /*<<< orphan*/  t_termios; } ;
struct termios32 {int dummy; } ;
struct termios {int c_cflag; int c_lflag; int /*<<< orphan*/ * c_cc; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; int /*<<< orphan*/  c_ospeed; int /*<<< orphan*/  c_ispeed; } ;
struct session {void* s_ttypgrpid; struct tty* s_ttyp; int /*<<< orphan*/  s_ttyvp; } ;
struct pgrp {void* pg_id; struct session* pg_session; int /*<<< orphan*/  pg_jobc; } ;
typedef  TYPE_2__* proc_t ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_18__ {int (* l_open ) (int /*<<< orphan*/ ,struct tty*) ;int /*<<< orphan*/  (* l_rint ) (int /*<<< orphan*/ ,struct tty*) ;int /*<<< orphan*/  (* l_close ) (struct tty*,int) ;} ;
struct TYPE_17__ {int p_lflag; int p_sigignore; int /*<<< orphan*/  p_acflag; int /*<<< orphan*/  p_flag; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* d_ioctl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CIGNORE ; 
 int /*<<< orphan*/  CLOCAL ; 
 int /*<<< orphan*/  CLR (int,int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int EBUSY ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int ENOTTY ; 
 int ENXIO ; 
 int EPERM ; 
 int /*<<< orphan*/  EXTPROC ; 
#define  FIOASYNC 168 
#define  FIONBIO 167 
#define  FIONREAD 166 
 int /*<<< orphan*/  FLUSHO ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  ICANON ; 
 int ISSET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KMIOCDISABLCONS ; 
 void* NO_PID ; 
 int /*<<< orphan*/  OSBitOrAtomic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  OTIOCSETD 165 
 int /*<<< orphan*/  PENDIN ; 
 struct pgrp* PGRP_NULL ; 
 int /*<<< orphan*/  P_CONTROLT ; 
 int P_LPPWAIT ; 
 struct session* SESSION_NULL ; 
 int /*<<< orphan*/  SESS_LEADER (TYPE_2__*,struct session*) ; 
 int /*<<< orphan*/  SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIGWINCH ; 
#define  TIOCCONS 164 
#define  TIOCDRAIN 163 
#define  TIOCEXCL 162 
#define  TIOCFLUSH 161 
#define  TIOCGDRAINWAIT 160 
#define  TIOCGETA_32 159 
#define  TIOCGETA_64 158 
#define  TIOCGETD 157 
#define  TIOCGPGRP 156 
#define  TIOCGWINSZ 155 
#define  TIOCIXOFF 154 
#define  TIOCIXON 153 
#define  TIOCLBIC 152 
#define  TIOCLBIS 151 
#define  TIOCLSET 150 
#define  TIOCNXCL 149 
#define  TIOCOUTQ 148 
#define  TIOCSCONS 147 
#define  TIOCSCTTY 146 
#define  TIOCSDRAINWAIT 145 
#define  TIOCSETAF_32 144 
#define  TIOCSETAF_64 143 
#define  TIOCSETAW_32 142 
#define  TIOCSETAW_64 141 
#define  TIOCSETA_32 140 
#define  TIOCSETA_64 139 
#define  TIOCSETC 138 
#define  TIOCSETD 137 
#define  TIOCSETN 136 
#define  TIOCSETP 135 
#define  TIOCSLTC 134 
#define  TIOCSPGRP 133 
#define  TIOCSTART 132 
#define  TIOCSTAT 131 
#define  TIOCSTI 130 
#define  TIOCSTOP 129 
#define  TIOCSWINSZ 128 
 int /*<<< orphan*/  TSA_CARR_ON (struct tty*) ; 
 int /*<<< orphan*/  TSA_HUP_OR_INPUT (struct tty*) ; 
 int /*<<< orphan*/  TSA_OCOMPLETE (struct tty*) ; 
 int /*<<< orphan*/  TSA_OLOWAT (struct tty*) ; 
 int /*<<< orphan*/  TS_ASYNC ; 
 int /*<<< orphan*/  TS_CARR_ON ; 
 int /*<<< orphan*/  TS_CONNECTED ; 
 int /*<<< orphan*/  TS_PGRPHUP ; 
 int /*<<< orphan*/  TS_TTSTOP ; 
 int /*<<< orphan*/  TS_XCLUDE ; 
 int /*<<< orphan*/  TS_ZOMBIE ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  catq (struct clist*,struct clist*) ; 
 TYPE_13__* cdevsw ; 
 struct tty* constty ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  isbackground (TYPE_2__*,struct tty*) ; 
 int /*<<< orphan*/  isctty (TYPE_2__*,struct tty*) ; 
 int /*<<< orphan*/  isctty_sp (TYPE_2__*,struct tty*,struct session*) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 TYPE_9__* linesw ; 
 size_t major (int /*<<< orphan*/ ) ; 
 int nlinesw ; 
 int /*<<< orphan*/  pg_rele (struct pgrp*) ; 
 struct pgrp* pgfind (int) ; 
 int /*<<< orphan*/  pgsignal (struct pgrp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 struct pgrp* proc_pgrp (TYPE_2__*) ; 
 struct session* proc_session (TYPE_2__*) ; 
 int /*<<< orphan*/  session_lock (struct session*) ; 
 int /*<<< orphan*/  session_rele (struct session*) ; 
 int /*<<< orphan*/  session_unlock (struct session*) ; 
 int sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int stub3 (struct tty*,struct termios*) ; 
 int /*<<< orphan*/  stub4 (struct tty*,int) ; 
 int stub5 (int /*<<< orphan*/ ,struct tty*) ; 
 int stub6 (int /*<<< orphan*/ ,struct tty*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,struct tty*) ; 
 int suser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  termios32to64 (struct termios32*,struct user_termios*) ; 
 int /*<<< orphan*/  termios64to32 (struct user_termios*,struct termios32*) ; 
 int ttcompat (struct tty*,int,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int ttnread (struct tty*) ; 
 int /*<<< orphan*/  ttsetwater (struct tty*) ; 
 int /*<<< orphan*/  ttstart (struct tty*) ; 
 int /*<<< orphan*/  ttwakeup (struct tty*) ; 
 int /*<<< orphan*/  ttwwakeup (struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_pgsignal (struct tty*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttyblock (struct tty*) ; 
 int /*<<< orphan*/  ttyflush (struct tty*,int) ; 
 int /*<<< orphan*/  ttyfree (struct tty*) ; 
 int /*<<< orphan*/  ttyhold (struct tty*) ; 
 int /*<<< orphan*/  ttyinfo_locked (struct tty*) ; 
 int /*<<< orphan*/  ttystop (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyunblock (struct tty*) ; 
 int ttywait (struct tty*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

int
ttioctl_locked(struct tty *tp, u_long cmd, caddr_t data, int flag, proc_t p)
{
	int error = 0;
	int bogusData = 1;
	struct uthread *ut;
	struct pgrp *pg, *oldpg;
	struct session *sessp, *oldsessp;
	struct tty *oldtp;

	TTY_LOCK_OWNED(tp);	/* debug assert */

	ut = (struct uthread *)get_bsdthread_info(current_thread());
	/* If the ioctl involves modification, signal if in the background. */
	switch (cmd) {
	case TIOCIXON:
	case TIOCIXOFF:
	case  TIOCDRAIN:
	case  TIOCFLUSH:
	case TIOCSTOP:
	case TIOCSTART:
	case  TIOCSETA_32:
	case  TIOCSETA_64:
	case  TIOCSETD:
	case  TIOCSETAF_32:
	case  TIOCSETAF_64:
	case  TIOCSETAW_32:
	case  TIOCSETAW_64:
	case  TIOCSPGRP:
	case  TIOCSTAT:
	case  TIOCSTI:
	case  TIOCSWINSZ:
	case  TIOCLBIC:
	case  TIOCLBIS:
	case  TIOCLSET:
	case  TIOCSETC:
	case OTIOCSETD:
	case  TIOCSETN:
	case  TIOCSETP:
	case  TIOCSLTC:
		while (isbackground(p, tp) &&
		    (p->p_lflag & P_LPPWAIT) == 0 &&
		    (p->p_sigignore & sigmask(SIGTTOU)) == 0 &&
		    (ut->uu_sigmask & sigmask(SIGTTOU)) == 0) {
			pg = proc_pgrp(p);
			if (pg == PGRP_NULL) {
				error = EIO;
				goto out;
			}
			/* SAFE: All callers drop the lock on return */
			tty_unlock(tp);
			if (pg->pg_jobc == 0) {
				pg_rele(pg);
				tty_lock(tp);
				error = EIO;
				goto out;
			}
			pgsignal(pg, SIGTTOU, 1);
			pg_rele(pg);
			tty_lock(tp);


			/*
			 * We signalled ourself, so we need to act as if we
			 * have been "interrupted" from a "sleep" to act on
			 * the signal.  If it's a signal that stops the
			 * process, that's handled in the signal sending code.
			 */
			error = EINTR;
			goto out;
		}
		break;
	}

	switch (cmd) {			/* Process the ioctl. */
	case FIOASYNC:			/* set/clear async i/o */
		if (*(int *)data)
			SET(tp->t_state, TS_ASYNC);
		else
			CLR(tp->t_state, TS_ASYNC);
		break;
	case FIONBIO:			/* set/clear non-blocking i/o */
		break;			/* XXX: delete. */
	case FIONREAD:			/* get # bytes to read */
		*(int *)data = ttnread(tp);
		break;
	case TIOCEXCL:			/* set exclusive use of tty */
		SET(tp->t_state, TS_XCLUDE);
		break;
	case TIOCFLUSH: {		/* flush buffers */
		int flags = *(int *)data;

		if (flags == 0)
			flags = FREAD | FWRITE;
		else
			flags &= FREAD | FWRITE;
		ttyflush(tp, flags);
		break;
	}
	case TIOCSCONS: {
		/* Set current console device to this line */
		data = (caddr_t) &bogusData;

		/* No break - Fall through to BSD code */
	}
	case TIOCCONS: {			/* become virtual console */
		if (*(int *)data) {
			if (constty && constty != tp &&
			    ISSET(constty->t_state, TS_CONNECTED)) {
				error = EBUSY;
				goto out;
			}
			if ( (error = suser(kauth_cred_get(), &p->p_acflag)) ) 
				goto out;
			constty = tp;
		} else if (tp == constty) {
			constty = NULL;
		}
		if (constty) {
			(*cdevsw[major(constty->t_dev)].d_ioctl)
				(constty->t_dev, KMIOCDISABLCONS, NULL, 0, p);
		} else {
			(*cdevsw[major(tp->t_dev)].d_ioctl)
				(tp->t_dev, KMIOCDISABLCONS, NULL, 0, p);
		}
		break;
	}
	case TIOCDRAIN:			/* wait till output drained */
		error = ttywait(tp);
		if (error)
			goto out;
		break;
	case TIOCGETA_32:		/* get termios struct */
#ifdef __LP64__
		termios64to32((struct user_termios *)&tp->t_termios, (struct termios32 *)data);
#else
		bcopy(&tp->t_termios, data, sizeof(struct termios));
#endif
		break;
	case TIOCGETA_64:		/* get termios struct */
#ifdef __LP64__
		bcopy(&tp->t_termios, data, sizeof(struct termios));
#else
		termios32to64((struct termios32 *)&tp->t_termios, (struct user_termios *)data);
#endif
		break;
	case TIOCGETD:			/* get line discipline */
		*(int *)data = tp->t_line;
		break;
	case TIOCGWINSZ:		/* get window size */
		*(struct winsize *)data = tp->t_winsize;
		break;
	case TIOCGPGRP:			/* get pgrp of tty */
		if (!isctty(p, tp)) {
			error = ENOTTY;
			goto out;
		}
		*(int *)data = tp->t_pgrp ? tp->t_pgrp->pg_id : NO_PID;
		break;
#ifdef TIOCHPCL
	case TIOCHPCL:			/* hang up on last close */
		SET(tp->t_cflag, HUPCL);
		break;
#endif
	case TIOCNXCL:			/* reset exclusive use of tty */
		CLR(tp->t_state, TS_XCLUDE);
		break;
	case TIOCOUTQ:			/* output queue size */
		*(int *)data = tp->t_outq.c_cc;
		break;
	case TIOCSETA_32:			/* set termios struct */
	case TIOCSETA_64:
	case TIOCSETAW_32:			/* drain output, set */
	case TIOCSETAW_64:
	case TIOCSETAF_32:		/* drn out, fls in, set */
	case TIOCSETAF_64:
	{		/* drn out, fls in, set */
		struct termios *t = (struct termios *)data;
		struct termios lcl_termios;

#ifdef __LP64__
		if (cmd==TIOCSETA_32 || cmd==TIOCSETAW_32 || cmd==TIOCSETAF_32) {
			termios32to64((struct termios32 *)data, (struct user_termios *)&lcl_termios);
			t = &lcl_termios;
		}
#else
		if (cmd==TIOCSETA_64 || cmd==TIOCSETAW_64 || cmd==TIOCSETAF_64) {
			termios64to32((struct user_termios *)data, (struct termios32 *)&lcl_termios);
			t = &lcl_termios;
		}
#endif
#if 0
	/* XXX bogus test; always false */
		if (t->c_ispeed < 0 || t->c_ospeed < 0) {
			error = EINVAL;
			goto out;
		}
#endif	/* 0 - leave in; may end up being a conformance issue */
		if (t->c_ispeed == 0)
			t->c_ispeed = t->c_ospeed;
		if (cmd == TIOCSETAW_32 || cmd == TIOCSETAF_32 ||
		    cmd == TIOCSETAW_64 || cmd == TIOCSETAF_64) {
			error = ttywait(tp);
			if (error) {
				goto out;
			}
			if (cmd == TIOCSETAF_32 || cmd == TIOCSETAF_64)
				ttyflush(tp, FREAD);
		}
		if (!ISSET(t->c_cflag, CIGNORE)) {
			/*
			 * Set device hardware.
			 */
			if (tp->t_param && (error = (*tp->t_param)(tp, t))) {
				goto out;
			}
			if (ISSET(t->c_cflag, CLOCAL) &&
			    !ISSET(tp->t_cflag, CLOCAL)) {
				/*
				 * XXX disconnections would be too hard to
				 * get rid of without this kludge.  The only
				 * way to get rid of controlling terminals
				 * is to exit from the session leader.
				 */
				CLR(tp->t_state, TS_ZOMBIE);

				wakeup(TSA_CARR_ON(tp));
				ttwakeup(tp);
				ttwwakeup(tp);
			}
			if ((ISSET(tp->t_state, TS_CARR_ON) ||
			     ISSET(t->c_cflag, CLOCAL)) &&
			    !ISSET(tp->t_state, TS_ZOMBIE))
				SET(tp->t_state, TS_CONNECTED);
			else
				CLR(tp->t_state, TS_CONNECTED);
			tp->t_cflag = t->c_cflag;
			tp->t_ispeed = t->c_ispeed;
			tp->t_ospeed = t->c_ospeed;
			ttsetwater(tp);
		}
		if (ISSET(t->c_lflag, ICANON) != ISSET(tp->t_lflag, ICANON) &&
		    cmd != TIOCSETAF_32 && cmd != TIOCSETAF_64) {
			if (ISSET(t->c_lflag, ICANON))
				SET(tp->t_lflag, PENDIN);
			else {
				/*
				 * XXX we really shouldn't allow toggling
				 * ICANON while we're in a non-termios line
				 * discipline.  Now we have to worry about
				 * panicing for a null queue.
				 */
				if (tp->t_rawq.c_cs && tp->t_canq.c_cs) {
				    struct clist tq;

				    catq(&tp->t_rawq, &tp->t_canq);
				    tq = tp->t_rawq;
				    tp->t_rawq = tp->t_canq;
				    tp->t_canq = tq;
				}
				CLR(tp->t_lflag, PENDIN);
			}
			ttwakeup(tp);
		}
		tp->t_iflag = t->c_iflag;
		tp->t_oflag = t->c_oflag;
		/*
		 * Make the EXTPROC bit read only.
		 */
		if (ISSET(tp->t_lflag, EXTPROC))
			SET(t->c_lflag, EXTPROC);
		else
			CLR(t->c_lflag, EXTPROC);
		tp->t_lflag = t->c_lflag | ISSET(tp->t_lflag, PENDIN);
		if (t->c_cc[VMIN] != tp->t_cc[VMIN] ||
		    t->c_cc[VTIME] != tp->t_cc[VTIME])
			ttwakeup(tp);
		bcopy(t->c_cc, tp->t_cc, sizeof(t->c_cc));
		break;
	}
	case TIOCSETD: {		/* set line discipline */
		int t = *(int *)data;
		dev_t device = tp->t_dev;

		if (t >= nlinesw || t < 0) {
			error = ENXIO;
			goto out;
		}
		/*
		 * If the new line discipline is not equal to the old one,
		 * close the old one and open the new one.
		 */
		if (t != tp->t_line) {
			(*linesw[tp->t_line].l_close)(tp, flag);
			error = (*linesw[t].l_open)(device, tp);
			if (error) {
				/* This is racy; it's possible to lose both */
				(void)(*linesw[tp->t_line].l_open)(device, tp);
				goto out;
			}
			tp->t_line = t;
		}
		break;
	}
	case TIOCSTART:			/* start output, like ^Q */
		if (ISSET(tp->t_state, TS_TTSTOP) ||
		    ISSET(tp->t_lflag, FLUSHO)) {
			CLR(tp->t_lflag, FLUSHO);
			CLR(tp->t_state, TS_TTSTOP);
			ttstart(tp);
		}
		break;
	case TIOCSTI:			/* simulate terminal input */
		if (suser(kauth_cred_get(), NULL) && (flag & FREAD) == 0) {
			error = EPERM;
			goto out;
		}
		if (suser(kauth_cred_get(), NULL) && !isctty(p, tp)) {
			error = EACCES;
			goto out;
		}
		(*linesw[tp->t_line].l_rint)(*(u_char *)data, tp);
		break;
	case TIOCSTOP:			/* stop output, like ^S */
		if (!ISSET(tp->t_state, TS_TTSTOP)) {
			SET(tp->t_state, TS_TTSTOP);
                        ttystop(tp, 0);
		}
		break;
	case TIOCIXON:
		ttyunblock(tp);
		break;
	case TIOCIXOFF:
		ttyblock(tp);
		break;
	case TIOCSCTTY:			/* become controlling tty */
		/* Session ctty vnode pointer set in vnode layer. */
		sessp = proc_session(p);
		if (sessp == SESSION_NULL) {
			error = EPERM;
			goto out;
		}

		/*
		 * This can only be done by a session leader.
		 */
		if (!SESS_LEADER(p, sessp)) {
			/* SAFE: All callers drop the lock on return */
			tty_unlock(tp);
			session_rele(sessp);
			tty_lock(tp);
			error = EPERM;
			goto out;
		}
		/*
		 * If this terminal is already the controlling terminal for the
		 * session, nothing to do here.
		 */
		if (tp->t_session == sessp) {
			/* SAFE: All callers drop the lock on return */
			tty_unlock(tp);
			session_rele(sessp);
			tty_lock(tp);
			error = 0;
			goto out;
		}
		pg = proc_pgrp(p);
		/*
		 * Deny if the terminal is already attached to another session or
		 * the session already has a terminal vnode.
		 */
		session_lock(sessp);
		if (sessp->s_ttyvp || tp->t_session) {
			session_unlock(sessp);
			/* SAFE: All callers drop the lock on return */
			tty_unlock(tp);
			if (pg != PGRP_NULL) {
				pg_rele(pg);
			}
			session_rele(sessp);
			tty_lock(tp);
			error = EPERM;
			goto out;
		}
		sessp->s_ttypgrpid = pg->pg_id;
		oldtp = sessp->s_ttyp;
		ttyhold(tp);
		sessp->s_ttyp = tp;
		session_unlock(sessp);
		proc_list_lock();
		oldsessp = tp->t_session;
		oldpg = tp->t_pgrp;
		if (oldsessp != SESSION_NULL)
			oldsessp->s_ttypgrpid = NO_PID;
		/* do not drop refs on sessp and pg as tp holds them */
		tp->t_session = sessp;
		tp->t_pgrp = pg;
		proc_list_unlock();
		OSBitOrAtomic(P_CONTROLT, &p->p_flag);
		/* SAFE: All callers drop the lock on return */
		tty_unlock(tp);
		/* drop the reference on prev session and pgrp */
		if (oldsessp != SESSION_NULL)
			session_rele(oldsessp);
		if (oldpg != PGRP_NULL)
			pg_rele(oldpg);
		if (NULL != oldtp)
			ttyfree(oldtp);
		tty_lock(tp);
		break;

	case TIOCSPGRP: {		/* set pgrp of tty */
		struct pgrp *pgrp = PGRP_NULL;

		sessp = proc_session(p);
		if (!isctty_sp(p, tp, sessp)) {
			if (sessp != SESSION_NULL)
				session_rele(sessp);
			error = ENOTTY;
			goto out;
		}
		else if ((pgrp = pgfind(*(int *)data)) == PGRP_NULL) {
			if (sessp != SESSION_NULL)
				session_rele(sessp);
			error = EINVAL;
			goto out;
		 } else if (pgrp->pg_session != sessp) {
			/* SAFE: All callers drop the lock on return */
			tty_unlock(tp);
			if (sessp != SESSION_NULL)
				session_rele(sessp);
			pg_rele(pgrp);
			tty_lock(tp);
			error = EPERM;
			goto out;
		}
		/*
		 * The session leader is going away and is possibly going to revoke
		 * the terminal, we can't change the process group when that is the
		 * case.
		 */
		if (ISSET(tp->t_state, TS_PGRPHUP)) {
			if (sessp != SESSION_NULL)
				session_rele(sessp);
			pg_rele(pgrp);
			error = EPERM;
			goto out;
		}
		proc_list_lock();
		oldpg = tp->t_pgrp;
		tp->t_pgrp = pgrp;
		sessp->s_ttypgrpid = pgrp->pg_id;
		proc_list_unlock();

		/*
		 * Wakeup readers to recheck if they are still the foreground
		 * process group.
		 *
		 * ttwakeup() isn't called because the readers aren't getting
		 * woken up becuse there is something to read but to force
		 * the re-evaluation of their foreground process group status.
		 *
		 * Ordinarily leaving these readers waiting wouldn't be an issue
		 * as launchd would send them a termination signal eventually
		 * (if nobody else does). But if this terminal happens to be
		 * /dev/console, launchd itself could get blocked forever behind
		 * a revoke of /dev/console and leave the system deadlocked.
		 */
		wakeup(TSA_HUP_OR_INPUT(tp));

		/* SAFE: All callers drop the lock on return */
		tty_unlock(tp);
		if (oldpg != PGRP_NULL)
			pg_rele(oldpg);
		if (sessp != SESSION_NULL)
			session_rele(sessp);
		tty_lock(tp);
		break;
	}
	case TIOCSTAT:			/* simulate control-T */
		ttyinfo_locked(tp);
		break;
	case TIOCSWINSZ:		/* set window size */
		if (bcmp((caddr_t)&tp->t_winsize, data,
		    sizeof (struct winsize))) {
			tp->t_winsize = *(struct winsize *)data;
			/* SAFE: All callers drop the lock on return */
			tty_unlock(tp);
			tty_pgsignal(tp, SIGWINCH, 1);
			tty_lock(tp);
		}
		break;
	case TIOCSDRAINWAIT:
		error = suser(kauth_cred_get(), &p->p_acflag);
		if (error) {
			goto out;
		}
		tp->t_timeout = *(int *)data * hz;
		wakeup(TSA_OCOMPLETE(tp));
		wakeup(TSA_OLOWAT(tp));
		break;
	case TIOCGDRAINWAIT:
		*(int *)data = tp->t_timeout / hz;
		break; 
	default:
		error = ttcompat(tp, cmd, data, flag, p);
		goto out;
	}

	error = 0;
out:
	return(error);
}
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
struct TYPE_6__ {int c_cc; } ;
struct TYPE_5__ {int c_cc; } ;
struct TYPE_4__ {int c_cc; } ;
struct tty {int t_state; int t_lflag; TYPE_3__ t_canq; TYPE_2__ t_rawq; TYPE_1__ t_outq; } ;
struct ptmx_ioctl {int pt_flags; int /*<<< orphan*/  pt_ucntl; int /*<<< orphan*/  pt_send; } ;
struct knote {int kn_filter; int kn_data; int /*<<< orphan*/  kn_flags; } ;

/* Variables and functions */
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int /*<<< orphan*/  EV_EOF ; 
 int ICANON ; 
 int PF_PKT ; 
 int PF_REMOTE ; 
 int PF_UCNTL ; 
 int TS_CONNECTED ; 
 int TS_TTSTOP ; 
 int TS_ZOMBIE ; 
 int /*<<< orphan*/  TTYHOG ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  panic (char*,int,struct knote*,struct tty*) ; 

__attribute__((used)) static int
ptmx_kqops_common(struct knote *kn, struct ptmx_ioctl *pti, struct tty *tp)
{
	int retval = 0;

	TTY_LOCK_OWNED(tp);

	/* disconnects should force a wakeup (EOF) */
	if (!(tp->t_state & TS_CONNECTED)) {
		kn->kn_flags |= EV_EOF;
		return 1;
	}

	switch (kn->kn_filter) {
	case EVFILT_READ:
		/* there's data on the TTY and it's not stopped */
		if (tp->t_outq.c_cc && !(tp->t_state & TS_TTSTOP)) {
			retval = tp->t_outq.c_cc;
			kn->kn_data = retval;
		} else if (((pti->pt_flags & PF_PKT) && pti->pt_send) ||
				((pti->pt_flags & PF_UCNTL) && pti->pt_ucntl)) {
			retval = 1;
		}
		break;

	case EVFILT_WRITE:
		if (pti->pt_flags & PF_REMOTE) {
			if (tp->t_canq.c_cc == 0) {
				retval = TTYHOG - 1;
			}
		} else {
			retval = (TTYHOG - 2) - (tp->t_rawq.c_cc + tp->t_canq.c_cc);
			if (tp->t_canq.c_cc == 0 && (tp->t_lflag & ICANON)) {
				retval = 1;
			}
			if (retval < 0) {
				retval = 0;
			}
		}
		break;

	default:
		panic("ptmx kevent: unexpected filter: %d, kn = %p, tty = %p",
				kn->kn_filter, kn, tp);
		break;
	}

	if (tp->t_state & TS_ZOMBIE) {
		kn->kn_flags |= EV_EOF;
		retval = 1;
	}

	return retval;
}
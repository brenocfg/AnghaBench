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
struct TYPE_2__ {scalar_t__ c_cc; scalar_t__ c_cn; } ;
struct tty {int t_state; TYPE_1__ t_outq; scalar_t__ t_lowat; } ;
struct knote {int kn_filter; int /*<<< orphan*/  kn_flags; scalar_t__ kn_data; } ;

/* Variables and functions */
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int /*<<< orphan*/  EV_EOF ; 
 int TS_CONNECTED ; 
 int TS_ZOMBIE ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  panic (char*,int,struct knote*,struct tty*) ; 
 scalar_t__ ttnread (struct tty*) ; 

__attribute__((used)) static int
ptsd_kqops_common(struct knote *kn, struct tty *tp)
{
	int retval = 0;

	TTY_LOCK_OWNED(tp);

	switch (kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_data = ttnread(tp);
		if (kn->kn_data > 0) {
			retval = 1;
		}
		break;

	case EVFILT_WRITE:
		if ((tp->t_outq.c_cc <= tp->t_lowat) &&
			(tp->t_state & TS_CONNECTED)) {
			kn->kn_data = tp->t_outq.c_cn - tp->t_outq.c_cc;
			retval = 1;
		}
		break;

	default:
		panic("ptsd kevent: unexpected filter: %d, kn = %p, tty = %p",
				kn->kn_filter, kn, tp);
		break;
	}

	if (tp->t_state & TS_ZOMBIE) {
		kn->kn_flags |= EV_EOF;
		retval = 1;
	}

	return retval;
}
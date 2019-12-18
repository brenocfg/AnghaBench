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
struct TYPE_2__ {int c_cc; } ;
struct tty {int t_state; int t_lowat; int t_hiwat; int /*<<< orphan*/  t_wsel; int /*<<< orphan*/  t_rsel; TYPE_1__ t_outq; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int ENXIO ; 
 int FMARK ; 
#define  FREAD 129 
#define  FWRITE 128 
 int TS_CONNECTED ; 
 int TS_ZOMBIE ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  selrecord (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int ttnread (struct tty*) ; 

int
ttyselect(struct tty *tp, int rw, void *wql, proc_t p)
{
	int retval = 0;
	/*
	 * Attaching knotes to TTYs needs to call selrecord in order to hook
	 * up the waitq to the selinfo, regardless of data being ready.  See
	 * filt_ttyattach.
	 */
	bool needs_selrecord = rw & FMARK;
	rw &= ~FMARK;

	if (tp == NULL) {
		return ENXIO;
	}

	TTY_LOCK_OWNED(tp);

	if (tp->t_state & TS_ZOMBIE) {
		retval = 1;
		goto out;
	}

	switch (rw) {
	case FREAD:
		retval = ttnread(tp);
		if (retval > 0) {
			break;
		}

		selrecord(p, &tp->t_rsel, wql);
		break;
	case FWRITE:
		if ((tp->t_outq.c_cc <= tp->t_lowat) &&
		    (tp->t_state & TS_CONNECTED)) {
			retval = tp->t_hiwat - tp->t_outq.c_cc;
			break;
		}

		selrecord(p, &tp->t_wsel, wql);
		break;
	}

out:
	if (retval > 0 && needs_selrecord) {
		switch (rw) {
		case FREAD:
			selrecord(p, &tp->t_rsel, wql);
			break;
		case FWRITE:
			selrecord(p, &tp->t_wsel, wql);
			break;
		}
	}

	return retval;
}
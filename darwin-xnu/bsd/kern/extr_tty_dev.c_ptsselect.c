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
struct tty {int t_lowat; int t_hiwat; int /*<<< orphan*/  t_wsel; TYPE_1__ t_outq; int /*<<< orphan*/  t_state; int /*<<< orphan*/  t_rsel; } ;
struct ptmx_ioctl {struct tty* pt_tty; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENXIO ; 
#define  FREAD 129 
#define  FWRITE 128 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_CONNECTED ; 
 int /*<<< orphan*/  TS_ZOMBIE ; 
 struct ptmx_ioctl* pty_get_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int ttnread (struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

int
ptsselect(dev_t dev, int rw, void *wql, proc_t p)
{
	struct ptmx_ioctl *pti = pty_get_ioctl(dev, 0, NULL);
	struct tty *tp;
	int retval = 0;

	if (pti == NULL)
		return (ENXIO);
	tp = pti->pt_tty;
	if (tp == NULL)
		return (ENXIO);

	tty_lock(tp);

	switch (rw) {
	case FREAD:
		if (ISSET(tp->t_state, TS_ZOMBIE)) {
			retval = 1;
			break;
		}

		retval = ttnread(tp);
		if (retval > 0) {
			break;
		}

		selrecord(p, &tp->t_rsel, wql);
		break;
	case FWRITE:
		if (ISSET(tp->t_state, TS_ZOMBIE)) {
			retval = 1;
			break;
		}

		if ((tp->t_outq.c_cc <= tp->t_lowat) &&
				ISSET(tp->t_state, TS_CONNECTED)) {
			retval = tp->t_hiwat - tp->t_outq.c_cc;
			break;
		}

		selrecord(p, &tp->t_wsel, wql);
		break;
	}

	tty_unlock(tp);
	return (retval);
}
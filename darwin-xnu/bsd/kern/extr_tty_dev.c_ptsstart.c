#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty {int t_state; int /*<<< orphan*/  t_dev; } ;
struct ptmx_ioctl {int pt_flags; int /*<<< orphan*/  pt_send; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREAD ; 
 int PF_STOPPED ; 
 int /*<<< orphan*/  TIOCPKT_START ; 
 int TS_TTSTOP ; 
 int /*<<< orphan*/  ptcwakeup (struct tty*,int /*<<< orphan*/ ) ; 
 struct ptmx_ioctl* pty_get_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ptsstart(struct tty *tp)
{
	struct ptmx_ioctl *pti = pty_get_ioctl(tp->t_dev, 0, NULL);
	if (pti == NULL)
		goto out;
	if (tp->t_state & TS_TTSTOP)
	        goto out;
	if (pti->pt_flags & PF_STOPPED) {
		pti->pt_flags &= ~PF_STOPPED;
		pti->pt_send = TIOCPKT_START;
	}
	ptcwakeup(tp, FREAD);
out:
	return;
}
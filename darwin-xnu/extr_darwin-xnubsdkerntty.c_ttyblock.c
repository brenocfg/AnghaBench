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
struct tty {scalar_t__* t_cc; int /*<<< orphan*/  t_state; int /*<<< orphan*/  t_outq; int /*<<< orphan*/  t_iflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXOFF ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_TBLOCK ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 size_t VSTOP ; 
 scalar_t__ _POSIX_VDISABLE ; 
 scalar_t__ putc (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttstart (struct tty*) ; 

void
ttyblock(struct tty *tp)
{
	TTY_LOCK_OWNED(tp);	/* debug assert */

	SET(tp->t_state, TS_TBLOCK);
	if (ISSET(tp->t_iflag, IXOFF) && tp->t_cc[VSTOP] != _POSIX_VDISABLE &&
	    putc(tp->t_cc[VSTOP], &tp->t_outq) != 0)
		CLR(tp->t_state, TS_TBLOCK);	/* try again later */
	ttstart(tp);
}
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
struct tty {int /*<<< orphan*/  t_winsize; int /*<<< orphan*/  t_state; int /*<<< orphan*/  t_cflag; int /*<<< orphan*/  t_dev; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCAL ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_CONNECTED ; 
 int /*<<< orphan*/  TS_ISOPEN ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

int
ttyopen(dev_t device, struct tty *tp)
{
	TTY_LOCK_OWNED(tp);	/* debug assert */

	tp->t_dev = device;

	if (!ISSET(tp->t_state, TS_ISOPEN)) {
		SET(tp->t_state, TS_ISOPEN);
		if (ISSET(tp->t_cflag, CLOCAL)) {
			SET(tp->t_state, TS_CONNECTED); }
		bzero(&tp->t_winsize, sizeof(tp->t_winsize));
	}

	return (0);
}
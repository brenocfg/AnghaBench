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
struct tty {int t_gen; int /*<<< orphan*/  t_lock; } ;

/* Variables and functions */
 int ERESTART ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 int msleep0 (void*,int /*<<< orphan*/ *,int,char const*,int,int (*) (int)) ; 

int
ttysleep(struct tty *tp, void *chan, int pri, const char *wmesg, int timo)
{
	int error;
	int gen;

	TTY_LOCK_OWNED(tp);

	gen = tp->t_gen;
	/* Use of msleep0() avoids conversion timo/timespec/timo */
	error = msleep0(chan, &tp->t_lock, pri, wmesg, timo, (int (*)(int))0);
	if (error)
		return (error);
	return (tp->t_gen == gen ? 0 : ERESTART);
}
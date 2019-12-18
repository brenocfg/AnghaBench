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
struct tty {int /*<<< orphan*/  t_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_LOCK_NOTOWNED (struct tty*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 

void
tty_lock(struct tty *tp)
{
	TTY_LOCK_NOTOWNED(tp);	/* debug assert */
	lck_mtx_lock(&tp->t_lock);
}
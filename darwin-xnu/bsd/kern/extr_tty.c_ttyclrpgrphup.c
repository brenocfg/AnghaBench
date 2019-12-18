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
struct tty {int /*<<< orphan*/  t_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_PGRPHUP ; 
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 

void
ttyclrpgrphup(struct tty *tp)
{
	TTY_LOCK_OWNED(tp);     /* debug assert */
	CLR(tp->t_state, TS_PGRPHUP);
}
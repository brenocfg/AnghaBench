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
struct tty {size_t t_line; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* l_rint ) (char,struct tty*) ;} ;

/* Variables and functions */
 struct tty** km_tty ; 
 TYPE_1__* linesw ; 
 int /*<<< orphan*/  stub1 (char,struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

void
cons_cinput(char ch)
{
	struct tty *tp = km_tty[0];	/* XXX */

	tty_lock(tp);
	(*linesw[tp->t_line].l_rint) (ch, tp);
	tty_unlock(tp);
}
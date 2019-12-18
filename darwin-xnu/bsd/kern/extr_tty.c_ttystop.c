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
struct tty {int /*<<< orphan*/  t_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* d_stop ) (struct tty*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_LOCK_OWNED (struct tty*) ; 
 TYPE_1__* cdevsw ; 
 size_t major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tty*,int) ; 

__attribute__((used)) static void
ttystop(struct tty *tp, int rw)
{
	TTY_LOCK_OWNED(tp);	/* debug assert */

	(*cdevsw[major(tp->t_dev)].d_stop)(tp, rw);
}
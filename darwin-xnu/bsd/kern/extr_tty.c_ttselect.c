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
struct tty {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {struct tty** d_ttys; } ;

/* Variables and functions */
 TYPE_1__* cdevsw ; 
 size_t major (int /*<<< orphan*/ ) ; 
 size_t minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int ttyselect (struct tty*,int,void*,int /*<<< orphan*/ ) ; 

int
ttselect(dev_t dev, int rw, void *wql, proc_t p)
{
	int	rv;
	struct tty *tp = cdevsw[major(dev)].d_ttys[minor(dev)];

	tty_lock(tp);
	rv =  ttyselect(tp, rw, wql, p);
	tty_unlock(tp);

	return (rv);
}
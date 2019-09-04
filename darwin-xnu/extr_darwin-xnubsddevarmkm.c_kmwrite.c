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
struct uio {int dummy; } ;
struct tty {size_t t_line; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int (* l_write ) (struct tty*,struct uio*,int) ;} ;

/* Variables and functions */
 struct tty** km_tty ; 
 TYPE_1__* linesw ; 
 size_t minor (int /*<<< orphan*/ ) ; 
 int stub1 (struct tty*,struct uio*,int) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

int
kmwrite(dev_t dev, struct uio * uio, int ioflag)
{
	int ret;
	struct tty *tp = km_tty[minor(dev)];

	tty_lock(tp);
	ret = (*linesw[tp->t_line].l_write)(tp, uio, ioflag);
	tty_unlock(tp);

	return (ret);
}
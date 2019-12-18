#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  driver_data; TYPE_2__* ldisc; scalar_t__ pgrp; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* flush_buffer ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  L_NOFLSH (struct tty_struct*) ; 
 int /*<<< orphan*/  i2InputFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_pgrp (scalar_t__,int,int) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 

__attribute__((used)) static inline void  isig(int sig, struct tty_struct *tty, int flush)
{
	/* FIXME: This is completely bogus */
	if (tty->pgrp)
		kill_pgrp(tty->pgrp, sig, 1);
	if (flush || !L_NOFLSH(tty)) {
		if ( tty->ldisc->ops->flush_buffer )  
			tty->ldisc->ops->flush_buffer(tty);
		i2InputFlush( tty->driver_data );
	}
}
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
struct tty_struct {scalar_t__ pgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  L_NOFLSH (struct tty_struct*) ; 
 int /*<<< orphan*/  kill_pgrp (scalar_t__,int,int) ; 
 int /*<<< orphan*/  n_tty_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 

__attribute__((used)) static inline void isig(int sig, struct tty_struct *tty, int flush)
{
	if (tty->pgrp)
		kill_pgrp(tty->pgrp, sig, 1);
	if (flush || !L_NOFLSH(tty)) {
		n_tty_flush_buffer(tty);
		tty_driver_flush_buffer(tty);
	}
}
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
struct tty {int dummy; } ;
struct pgrp {int dummy; } ;

/* Variables and functions */
 struct pgrp* PGRP_NULL ; 
 int /*<<< orphan*/  pg_rele (struct pgrp*) ; 
 int /*<<< orphan*/  pgrp_iterate (struct pgrp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pgsignal_callback ; 
 int /*<<< orphan*/  pgsignal_filt ; 
 struct pgrp* tty_pgrp (struct tty*) ; 

void
tty_pgsignal(struct tty *tp, int signum, int checkctty)
{
	struct pgrp * pg;

	pg = tty_pgrp(tp);
	if (pg != PGRP_NULL) {
		pgrp_iterate(pg, 0, pgsignal_callback, &signum, pgsignal_filt, &checkctty);
		pg_rele(pg);
	}
}
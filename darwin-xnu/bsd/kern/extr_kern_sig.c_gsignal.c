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
struct pgrp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pg_rele (struct pgrp*) ; 
 struct pgrp* pgfind (int) ; 
 int /*<<< orphan*/  pgsignal (struct pgrp*,int,int /*<<< orphan*/ ) ; 

void
gsignal(int pgid, int signum)
{
	struct pgrp *pgrp;

	if (pgid && (pgrp = pgfind(pgid))) {
		pgsignal(pgrp, signum, 0);
		pg_rele(pgrp);
	}
}
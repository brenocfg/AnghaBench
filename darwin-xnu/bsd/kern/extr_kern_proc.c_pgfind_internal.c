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
struct TYPE_3__ {struct pgrp* le_next; } ;
struct pgrp {scalar_t__ pg_id; TYPE_1__ pg_hash; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_4__ {struct pgrp* lh_first; } ;

/* Variables and functions */
 TYPE_2__* PGRPHASH (scalar_t__) ; 

struct pgrp *
pgfind_internal(pid_t pgid)
{
	struct pgrp *pgrp;

	for (pgrp = PGRPHASH(pgid)->lh_first; pgrp != 0; pgrp = pgrp->pg_hash.le_next)
		if (pgrp->pg_id == pgid)
			return (pgrp);
	return (NULL);
}
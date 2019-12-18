#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lck_grp_refcnt; } ;
typedef  TYPE_1__ lck_grp_t ;

/* Variables and functions */
 int /*<<< orphan*/  hw_atomic_add (int /*<<< orphan*/ *,int) ; 

void
lck_grp_reference(
	lck_grp_t	*grp)
{
	(void)hw_atomic_add(&grp->lck_grp_refcnt, 1);
}
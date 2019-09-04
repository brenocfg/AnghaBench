#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lck_grp_refcnt; } ;
typedef  TYPE_1__ lck_grp_t ;

/* Variables and functions */
 scalar_t__ hw_atomic_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 

void
lck_grp_deallocate(
	lck_grp_t	*grp)
{
	if (hw_atomic_sub(&grp->lck_grp_refcnt, 1) == 0)
	 	kfree(grp, sizeof(lck_grp_t));
}
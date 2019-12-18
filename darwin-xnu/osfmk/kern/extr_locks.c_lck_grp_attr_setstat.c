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
struct TYPE_3__ {int /*<<< orphan*/  grp_attr_val; } ;
typedef  TYPE_1__ lck_grp_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_GRP_ATTR_STAT ; 
 int /*<<< orphan*/  hw_atomic_or (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
lck_grp_attr_setstat(
	lck_grp_attr_t	*attr)
{
	(void)hw_atomic_or(&attr->grp_attr_val, LCK_GRP_ATTR_STAT);
}
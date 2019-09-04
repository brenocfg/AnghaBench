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
struct TYPE_3__ {int /*<<< orphan*/  lck_attr_val; } ;
typedef  TYPE_1__ lck_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_ATTR_RW_SHARED_PRIORITY ; 
 int /*<<< orphan*/  hw_atomic_or (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
lck_attr_rw_shared_priority(
	lck_attr_t	*attr)
{
	(void)hw_atomic_or(&attr->lck_attr_val, LCK_ATTR_RW_SHARED_PRIORITY);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* lck_rw_priv_excl; void* lck_rw_can_sleep; } ;
typedef  TYPE_1__ lck_rw_t ;
typedef  int /*<<< orphan*/  lck_grp_t ;
struct TYPE_9__ {int lck_attr_val; } ;
typedef  TYPE_2__ lck_attr_t ;

/* Variables and functions */
 TYPE_2__* LCK_ATTR_NULL ; 
 int LCK_ATTR_RW_SHARED_PRIORITY ; 
 int /*<<< orphan*/  LCK_TYPE_RW ; 
 TYPE_2__ LockDefaultLckAttr ; 
 void* TRUE ; 
 int /*<<< orphan*/  lck_grp_lckcnt_incr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
lck_rw_init(
	lck_rw_t	*lck,
	lck_grp_t	*grp,
	lck_attr_t	*attr)
{
	if (attr == LCK_ATTR_NULL)
		attr = &LockDefaultLckAttr;
	memset(lck, 0, sizeof(lck_rw_t));
	lck->lck_rw_can_sleep = TRUE;
	if ((attr->lck_attr_val & LCK_ATTR_RW_SHARED_PRIORITY) == 0)
		lck->lck_rw_priv_excl = TRUE;

	lck_grp_reference(grp);
	lck_grp_lckcnt_incr(grp, LCK_TYPE_RW);
}
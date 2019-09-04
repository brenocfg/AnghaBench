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
struct TYPE_3__ {scalar_t__ lck_rw_tag; } ;
typedef  TYPE_1__ lck_rw_t ;
typedef  int /*<<< orphan*/  lck_grp_t ;

/* Variables and functions */
 scalar_t__ LCK_RW_TAG_DESTROYED ; 
 int /*<<< orphan*/  LCK_TYPE_RW ; 
 int /*<<< orphan*/  lck_grp_deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_lckcnt_decr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
lck_rw_destroy(
	lck_rw_t	*lck,
	lck_grp_t	*grp)
{
	if (lck->lck_rw_tag == LCK_RW_TAG_DESTROYED)
		return;
#if MACH_LDEBUG
	lck_rw_assert(lck, LCK_RW_ASSERT_NOTHELD);
#endif
	lck->lck_rw_tag = LCK_RW_TAG_DESTROYED;
	lck_grp_lckcnt_decr(grp, LCK_TYPE_RW);
	lck_grp_deallocate(grp);
	return;
}
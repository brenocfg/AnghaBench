#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ lck_mtx_tag; int /*<<< orphan*/  lck_mtx_ptr; } ;
typedef  TYPE_1__ lck_mtx_t ;
typedef  int /*<<< orphan*/  lck_mtx_ext_t ;
typedef  int /*<<< orphan*/  lck_grp_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 scalar_t__ LCK_MTX_TAG_DESTROYED ; 
 scalar_t__ LCK_MTX_TAG_INDIRECT ; 
 int /*<<< orphan*/  LCK_TYPE_MTX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lck_grp_deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_lckcnt_decr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_assert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock_mark_destroyed (TYPE_1__*,int) ; 

void
lck_mtx_destroy(
	lck_mtx_t	*lck,
	lck_grp_t	*grp)
{
	boolean_t indirect;
	
	if (lck->lck_mtx_tag == LCK_MTX_TAG_DESTROYED)
		return;
#if MACH_LDEBUG
	lck_mtx_assert(lck, LCK_MTX_ASSERT_NOTOWNED);
#endif
	indirect = (lck->lck_mtx_tag == LCK_MTX_TAG_INDIRECT);

	lck_mtx_lock_mark_destroyed(lck, indirect);

	if (indirect)
		kfree(lck->lck_mtx_ptr, sizeof(lck_mtx_ext_t));
	lck_grp_lckcnt_decr(grp, LCK_TYPE_MTX);
	lck_grp_deallocate(grp);
	return;
}
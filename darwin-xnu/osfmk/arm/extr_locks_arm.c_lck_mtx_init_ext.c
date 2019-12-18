#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* lck_mtx_type; scalar_t__ lck_mtx_pri; scalar_t__ lck_mtx_waiters; int /*<<< orphan*/ * lck_mtx_ptr; int /*<<< orphan*/  lck_mtx_tag; } ;
typedef  TYPE_1__ lck_mtx_t ;
typedef  int /*<<< orphan*/  lck_mtx_ext_t ;
typedef  int /*<<< orphan*/  lck_grp_t ;
struct TYPE_10__ {int lck_attr_val; } ;
typedef  TYPE_2__ lck_attr_t ;

/* Variables and functions */
 int LCK_ATTR_DEBUG ; 
 TYPE_2__* LCK_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_MTX_TAG_INDIRECT ; 
 void* LCK_MTX_TYPE ; 
 int /*<<< orphan*/  LCK_TYPE_MTX ; 
 TYPE_2__ LockDefaultLckAttr ; 
 int /*<<< orphan*/  lck_grp_lckcnt_incr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_ext_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ordered_store_mtx (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
lck_mtx_init_ext(
		 lck_mtx_t * lck,
		 lck_mtx_ext_t * lck_ext,
		 lck_grp_t * grp,
		 lck_attr_t * attr)
{
	lck_attr_t     *lck_attr;

	if (attr != LCK_ATTR_NULL)
		lck_attr = attr;
	else
		lck_attr = &LockDefaultLckAttr;

	if ((lck_attr->lck_attr_val) & LCK_ATTR_DEBUG) {
		lck_mtx_ext_init(lck_ext, grp, lck_attr);
		lck->lck_mtx_tag = LCK_MTX_TAG_INDIRECT;
		lck->lck_mtx_ptr = lck_ext;
		lck->lck_mtx_type = LCK_MTX_TYPE;
	} else {
		lck->lck_mtx_waiters = 0;
		lck->lck_mtx_pri = 0;
		lck->lck_mtx_type = LCK_MTX_TYPE;
		ordered_store_mtx(lck, 0);
	}
	lck_grp_reference(grp);
	lck_grp_lckcnt_incr(grp, LCK_TYPE_MTX);
}
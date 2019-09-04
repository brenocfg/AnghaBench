#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/  lck_mtx_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  lck_mtx_attr; TYPE_4__* lck_mtx_grp; TYPE_2__ lck_mtx_deb; TYPE_1__ lck_mtx; } ;
typedef  TYPE_3__ lck_mtx_ext_t ;
struct TYPE_12__ {int lck_grp_attr; } ;
typedef  TYPE_4__ lck_grp_t ;
struct TYPE_13__ {int lck_attr_val; } ;
typedef  TYPE_5__ lck_attr_t ;

/* Variables and functions */
 int LCK_ATTR_DEBUG ; 
 int LCK_GRP_ATTR_STAT ; 
 int /*<<< orphan*/  LCK_MTX_ATTR_DEBUG ; 
 int /*<<< orphan*/  LCK_MTX_ATTR_STAT ; 
 int /*<<< orphan*/  LCK_MTX_TYPE ; 
 int /*<<< orphan*/  MUTEX_TAG ; 
 int /*<<< orphan*/  bzero (void*,int) ; 

void
lck_mtx_ext_init(
		 lck_mtx_ext_t * lck,
		 lck_grp_t * grp,
		 lck_attr_t * attr)
{
	bzero((void *) lck, sizeof(lck_mtx_ext_t));

	lck->lck_mtx.lck_mtx_type = LCK_MTX_TYPE;

	if ((attr->lck_attr_val) & LCK_ATTR_DEBUG) {
		lck->lck_mtx_deb.type = MUTEX_TAG;
		lck->lck_mtx_attr |= LCK_MTX_ATTR_DEBUG;
	}
	lck->lck_mtx_grp = grp;

	if (grp->lck_grp_attr & LCK_GRP_ATTR_STAT)
		lck->lck_mtx_attr |= LCK_MTX_ATTR_STAT;
}
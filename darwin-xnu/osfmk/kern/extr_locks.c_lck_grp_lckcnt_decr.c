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
typedef  int lck_type_t ;
struct TYPE_3__ {unsigned int lck_grp_spincnt; unsigned int lck_grp_mtxcnt; unsigned int lck_grp_rwcnt; } ;
typedef  TYPE_1__ lck_grp_t ;

/* Variables and functions */
#define  LCK_TYPE_MTX 130 
#define  LCK_TYPE_RW 129 
#define  LCK_TYPE_SPIN 128 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ hw_atomic_sub (unsigned int*,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

void
lck_grp_lckcnt_decr(
	lck_grp_t	*grp,
	lck_type_t	lck_type)
{
	unsigned int	*lckcnt;
	int		updated;

	switch (lck_type) {
	case LCK_TYPE_SPIN:
		lckcnt = &grp->lck_grp_spincnt;
		break;
	case LCK_TYPE_MTX:
		lckcnt = &grp->lck_grp_mtxcnt;
		break;
	case LCK_TYPE_RW:
		lckcnt = &grp->lck_grp_rwcnt;
		break;
	default:
		panic("lck_grp_lckcnt_decr(): invalid lock type: %d\n", lck_type);
		return;
	}

	updated = (int)hw_atomic_sub(lckcnt, 1);
	assert(updated >= 0);
}
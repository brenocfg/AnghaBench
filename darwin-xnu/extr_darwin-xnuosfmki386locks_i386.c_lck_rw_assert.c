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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  lck_rw_shared_count; int /*<<< orphan*/  lck_rw_want_upgrade; int /*<<< orphan*/  lck_rw_want_write; } ;
typedef  TYPE_1__ lck_rw_t ;

/* Variables and functions */
#define  LCK_RW_ASSERT_EXCLUSIVE 131 
#define  LCK_RW_ASSERT_HELD 130 
#define  LCK_RW_ASSERT_NOTHELD 129 
#define  LCK_RW_ASSERT_SHARED 128 
 int /*<<< orphan*/  panic (char*,TYPE_1__*,char*,unsigned int,int /*<<< orphan*/ ) ; 

void
lck_rw_assert(
	lck_rw_t	*lck,
	unsigned int	type)
{
	switch (type) {
	case LCK_RW_ASSERT_SHARED:
		if (lck->lck_rw_shared_count != 0) {
			return;
		}
		break;
	case LCK_RW_ASSERT_EXCLUSIVE:
		if ((lck->lck_rw_want_write ||
		     lck->lck_rw_want_upgrade) &&
		    lck->lck_rw_shared_count == 0) {
			return;
		}
		break;
	case LCK_RW_ASSERT_HELD:
		if (lck->lck_rw_want_write ||
		    lck->lck_rw_want_upgrade ||
		    lck->lck_rw_shared_count != 0) {
			return;
		}
		break;
	case LCK_RW_ASSERT_NOTHELD:
		if (!(lck->lck_rw_want_write ||
			  lck->lck_rw_want_upgrade ||
			  lck->lck_rw_shared_count != 0)) {
			return;
		}
		break;
	default:
		break;
	}

	panic("rw lock (%p)%s held (mode=%u), first word %08x\n", lck, (type == LCK_RW_ASSERT_NOTHELD ? "" : " not"), type, *(uint32_t *)lck);
}
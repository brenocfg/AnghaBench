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
struct TYPE_4__ {int /*<<< orphan*/  lck_rw_owner; int /*<<< orphan*/  lck_rw_want_upgrade; int /*<<< orphan*/  lck_rw_want_excl; int /*<<< orphan*/  lck_rw_shared_count; } ;
typedef  TYPE_1__ lck_rw_t ;

/* Variables and functions */
#define  LCK_RW_ASSERT_EXCLUSIVE 131 
#define  LCK_RW_ASSERT_HELD 130 
#define  LCK_RW_ASSERT_NOTHELD 129 
#define  LCK_RW_ASSERT_SHARED 128 
 int /*<<< orphan*/  THREAD_NULL ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*,char*,unsigned int) ; 

void
lck_rw_assert(
	lck_rw_t		*lck,
	unsigned int	type)
{
	switch (type) {
	case LCK_RW_ASSERT_SHARED:
		if ((lck->lck_rw_shared_count != 0) &&
		    (lck->lck_rw_owner == THREAD_NULL)) {
			return;
		}
		break;
	case LCK_RW_ASSERT_EXCLUSIVE:
		if ((lck->lck_rw_want_excl || lck->lck_rw_want_upgrade) &&
			(lck->lck_rw_shared_count == 0) &&
		    (lck->lck_rw_owner == current_thread())) {
			return;
		}
		break;
	case LCK_RW_ASSERT_HELD:
		if (lck->lck_rw_shared_count != 0)
			return;		// Held shared
		if ((lck->lck_rw_want_excl || lck->lck_rw_want_upgrade) &&
		    (lck->lck_rw_owner == current_thread())) {
			return;		// Held exclusive
		}
		break;
	case LCK_RW_ASSERT_NOTHELD:
		if ((lck->lck_rw_shared_count == 0) &&
		   !(lck->lck_rw_want_excl || lck->lck_rw_want_upgrade) &&
		    (lck->lck_rw_owner == THREAD_NULL)) {
			return;
		}
		break;
	default:
		break;
	}
	panic("rw lock (%p)%s held (mode=%u)", lck, (type == LCK_RW_ASSERT_NOTHELD ? "" : " not"), type);
}
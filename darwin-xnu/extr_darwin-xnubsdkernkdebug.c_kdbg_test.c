#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* kdebug_iops; } ;
struct TYPE_3__ {int cpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSDDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DBG_BSD_KDEBUG_TEST ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  KDBG (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  KDBG_DEBUG (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  KDBG_FILTERED (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  KDBG_RELEASE (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  KDBG_RELEASE_NOPROCFILT (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_2__ kd_ctrl_page ; 
 int kdbg_timestamp () ; 
 int /*<<< orphan*/  kernel_debug_enter (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t) ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kdbg_test(size_t flavor)
{
	int code = 0;
	int dummy_iop = 0;

#define KDEBUG_TEST_CODE(code) BSDDBG_CODE(DBG_BSD_KDEBUG_TEST, (code))
	switch (flavor) {
	case 1:
		/* try each macro */
		KDBG(KDEBUG_TEST_CODE(code)); code++;
		KDBG(KDEBUG_TEST_CODE(code), 1); code++;
		KDBG(KDEBUG_TEST_CODE(code), 1, 2); code++;
		KDBG(KDEBUG_TEST_CODE(code), 1, 2, 3); code++;
		KDBG(KDEBUG_TEST_CODE(code), 1, 2, 3, 4); code++;

		KDBG_RELEASE(KDEBUG_TEST_CODE(code)); code++;
		KDBG_RELEASE(KDEBUG_TEST_CODE(code), 1); code++;
		KDBG_RELEASE(KDEBUG_TEST_CODE(code), 1, 2); code++;
		KDBG_RELEASE(KDEBUG_TEST_CODE(code), 1, 2, 3); code++;
		KDBG_RELEASE(KDEBUG_TEST_CODE(code), 1, 2, 3, 4); code++;

		KDBG_FILTERED(KDEBUG_TEST_CODE(code)); code++;
		KDBG_FILTERED(KDEBUG_TEST_CODE(code), 1); code++;
		KDBG_FILTERED(KDEBUG_TEST_CODE(code), 1, 2); code++;
		KDBG_FILTERED(KDEBUG_TEST_CODE(code), 1, 2, 3); code++;
		KDBG_FILTERED(KDEBUG_TEST_CODE(code), 1, 2, 3, 4); code++;

		KDBG_RELEASE_NOPROCFILT(KDEBUG_TEST_CODE(code)); code++;
		KDBG_RELEASE_NOPROCFILT(KDEBUG_TEST_CODE(code), 1); code++;
		KDBG_RELEASE_NOPROCFILT(KDEBUG_TEST_CODE(code), 1, 2); code++;
		KDBG_RELEASE_NOPROCFILT(KDEBUG_TEST_CODE(code), 1, 2, 3); code++;
		KDBG_RELEASE_NOPROCFILT(KDEBUG_TEST_CODE(code), 1, 2, 3, 4); code++;

		KDBG_DEBUG(KDEBUG_TEST_CODE(code)); code++;
		KDBG_DEBUG(KDEBUG_TEST_CODE(code), 1); code++;
		KDBG_DEBUG(KDEBUG_TEST_CODE(code), 1, 2); code++;
		KDBG_DEBUG(KDEBUG_TEST_CODE(code), 1, 2, 3); code++;
		KDBG_DEBUG(KDEBUG_TEST_CODE(code), 1, 2, 3, 4); code++;
		break;

	case 2:
		if (kd_ctrl_page.kdebug_iops) {
			/* avoid the assertion in kernel_debug_enter for a valid IOP */
			dummy_iop = kd_ctrl_page.kdebug_iops[0].cpu_id;
		}

		/* ensure old timestamps are not emitted from kernel_debug_enter */
		kernel_debug_enter(dummy_iop, KDEBUG_TEST_CODE(code),
				100 /* very old timestamp */, 0, 0, 0,
				0, (uintptr_t)thread_tid(current_thread()));
		code++;
		kernel_debug_enter(dummy_iop, KDEBUG_TEST_CODE(code),
				kdbg_timestamp(), 0, 0, 0, 0,
				(uintptr_t)thread_tid(current_thread()));
		code++;
		break;

	default:
		return ENOTSUP;
	}
#undef KDEBUG_TEST_CODE

	return 0;
}
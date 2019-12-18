#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int SYS_OVERRIDE_CPU_THROTTLE ; 
 int SYS_OVERRIDE_FAST_JETSAM ; 
 int SYS_OVERRIDE_IO_THROTTLE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cpu_throttle_assert_cnt ; 
 scalar_t__ fast_jetsam_assert_cnt ; 
 scalar_t__ io_throttle_assert_cnt ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_override_lock ; 
 int /*<<< orphan*/  system_override_callouts (int,int) ; 

__attribute__((used)) static void
system_override_end(uint64_t flags)
{

	lck_mtx_assert(&sys_override_lock, LCK_MTX_ASSERT_OWNED);
	
	if (flags & SYS_OVERRIDE_IO_THROTTLE) {
		assert(io_throttle_assert_cnt > 0);
		io_throttle_assert_cnt--;
		if (io_throttle_assert_cnt == 0) {
			system_override_callouts(SYS_OVERRIDE_IO_THROTTLE, false);
		}
	}

	if (flags & SYS_OVERRIDE_CPU_THROTTLE) {
		assert(cpu_throttle_assert_cnt > 0);
		cpu_throttle_assert_cnt--;
		if (cpu_throttle_assert_cnt == 0) {
			system_override_callouts(SYS_OVERRIDE_CPU_THROTTLE, false);
		}
	}

	if (flags & SYS_OVERRIDE_FAST_JETSAM) {
		assert(fast_jetsam_assert_cnt > 0);
		fast_jetsam_assert_cnt--;
		if (fast_jetsam_assert_cnt == 0) {
			system_override_callouts(SYS_OVERRIDE_FAST_JETSAM, false);
		}
	}

}
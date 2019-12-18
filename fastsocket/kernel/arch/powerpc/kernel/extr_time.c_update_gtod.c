#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_2__ {int /*<<< orphan*/  tb_update_count; int /*<<< orphan*/  stamp_sec_fraction; struct timespec stamp_xtime; int /*<<< orphan*/  wtom_clock_nsec; int /*<<< orphan*/  wtom_clock_sec; void* tb_to_xs; void* stamp_xsec; void* tb_orig_stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_wmb () ; 
 TYPE_1__* vdso_data ; 

__attribute__((used)) static inline void update_gtod(u64 new_tb_stamp, u64 new_stamp_xsec,
			       u64 new_tb_to_xs, struct timespec *now,
			       struct timespec *wall_time,
			       u32 frac_sec)
{
	/*
	 * tb_update_count is used to allow the userspace gettimeofday code
	 * to assure itself that it sees a consistent view of the tb_to_xs and
	 * stamp_xsec variables.  It reads the tb_update_count, then reads
	 * tb_to_xs and stamp_xsec and then reads tb_update_count again.  If
	 * the two values of tb_update_count match and are even then the
	 * tb_to_xs and stamp_xsec values are consistent.  If not, then it
	 * loops back and reads them again until this criteria is met.
	 * We expect the caller to have done the first increment of
	 * vdso_data->tb_update_count already.
	 */
	vdso_data->tb_orig_stamp = new_tb_stamp;
	vdso_data->stamp_xsec = new_stamp_xsec;
	vdso_data->tb_to_xs = new_tb_to_xs;
	vdso_data->wtom_clock_sec = now->tv_sec;
	vdso_data->wtom_clock_nsec = now->tv_nsec;
	vdso_data->stamp_xtime = *wall_time;
	vdso_data->stamp_sec_fraction = frac_sec;
	smp_wmb();
	++(vdso_data->tb_update_count);
}
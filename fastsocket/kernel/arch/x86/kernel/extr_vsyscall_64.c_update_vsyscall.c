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
typedef  int /*<<< orphan*/  u32 ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct clocksource {int /*<<< orphan*/  shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  cycle_last; int /*<<< orphan*/  vread; } ;
struct TYPE_3__ {int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; int /*<<< orphan*/  mask; int /*<<< orphan*/  cycle_last; int /*<<< orphan*/  vread; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wall_time_coarse; struct timespec wall_to_monotonic; int /*<<< orphan*/  wall_time_nsec; int /*<<< orphan*/  wall_time_sec; TYPE_1__ clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __current_kernel_time () ; 
 TYPE_2__ vsyscall_gtod_data ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void update_vsyscall(struct timespec *wall_time, struct timespec *wtm,
			struct clocksource *clock, u32 mult)
{
	unsigned long flags;

	write_seqlock_irqsave(&vsyscall_gtod_data.lock, flags);
	/* copy vsyscall data */
	vsyscall_gtod_data.clock.vread = clock->vread;
	vsyscall_gtod_data.clock.cycle_last = clock->cycle_last;
	vsyscall_gtod_data.clock.mask = clock->mask;
	vsyscall_gtod_data.clock.mult = mult;
	vsyscall_gtod_data.clock.shift = clock->shift;
	vsyscall_gtod_data.wall_time_sec = wall_time->tv_sec;
	vsyscall_gtod_data.wall_time_nsec = wall_time->tv_nsec;
	vsyscall_gtod_data.wall_to_monotonic = *wtm;
	vsyscall_gtod_data.wall_time_coarse = __current_kernel_time();
	write_sequnlock_irqrestore(&vsyscall_gtod_data.lock, flags);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct clocksource {int /*<<< orphan*/  cycle_last; int /*<<< orphan*/  fsys_mmio; int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; int /*<<< orphan*/  mask; } ;
struct TYPE_6__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_5__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_2__ monotonic_time; TYPE_1__ wall_time; int /*<<< orphan*/  clk_cycle_last; int /*<<< orphan*/  clk_fsys_mmio; int /*<<< orphan*/  clk_shift; int /*<<< orphan*/  clk_mult; int /*<<< orphan*/  clk_mask; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 TYPE_4__ fsyscall_gtod_data ; 
 TYPE_3__ wall_to_monotonic ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void update_vsyscall(struct timespec *wall, struct clocksource *c)
{
        unsigned long flags;

        write_seqlock_irqsave(&fsyscall_gtod_data.lock, flags);

        /* copy fsyscall clock data */
        fsyscall_gtod_data.clk_mask = c->mask;
        fsyscall_gtod_data.clk_mult = c->mult;
        fsyscall_gtod_data.clk_shift = c->shift;
        fsyscall_gtod_data.clk_fsys_mmio = c->fsys_mmio;
        fsyscall_gtod_data.clk_cycle_last = c->cycle_last;

	/* copy kernel time structures */
        fsyscall_gtod_data.wall_time.tv_sec = wall->tv_sec;
        fsyscall_gtod_data.wall_time.tv_nsec = wall->tv_nsec;
        fsyscall_gtod_data.monotonic_time.tv_sec = wall_to_monotonic.tv_sec
							+ wall->tv_sec;
        fsyscall_gtod_data.monotonic_time.tv_nsec = wall_to_monotonic.tv_nsec
							+ wall->tv_nsec;

	/* normalize */
	while (fsyscall_gtod_data.monotonic_time.tv_nsec >= NSEC_PER_SEC) {
		fsyscall_gtod_data.monotonic_time.tv_nsec -= NSEC_PER_SEC;
		fsyscall_gtod_data.monotonic_time.tv_sec++;
	}

        write_sequnlock_irqrestore(&fsyscall_gtod_data.lock, flags);
}
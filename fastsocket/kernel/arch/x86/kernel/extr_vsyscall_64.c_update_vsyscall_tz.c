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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  sys_tz; } ;

/* Variables and functions */
 int /*<<< orphan*/  sys_tz ; 
 TYPE_1__ vsyscall_gtod_data ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void update_vsyscall_tz(void)
{
	unsigned long flags;

	write_seqlock_irqsave(&vsyscall_gtod_data.lock, flags);
	/* sys_tz has changed */
	vsyscall_gtod_data.sys_tz = sys_tz;
	write_sequnlock_irqrestore(&vsyscall_gtod_data.lock, flags);
}
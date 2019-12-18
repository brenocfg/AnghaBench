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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {struct timespec wall_to_monotonic; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__ timekeeper ; 
 int /*<<< orphan*/  timespec_to_ktime (struct timespec) ; 

ktime_t ktime_get_monotonic_offset(void)
{
	unsigned long seq;
	struct timespec wtom;

	do {
		seq = read_seqbegin(&timekeeper.lock);
		wtom = timekeeper.wall_to_monotonic;
	} while (read_seqretry(&timekeeper.lock, seq));

	return timespec_to_ktime(wtom);
}
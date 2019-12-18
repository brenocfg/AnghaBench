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
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_2__ {struct timespec raw_time; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__ timekeeper ; 
 int /*<<< orphan*/  timekeeping_get_ns_raw () ; 
 int /*<<< orphan*/  timespec_add_ns (struct timespec*,int /*<<< orphan*/ ) ; 

void getrawmonotonic(struct timespec *ts)
{
	unsigned long seq;
	s64 nsecs;

	do {
		seq = read_seqbegin(&timekeeper.lock);
		nsecs = timekeeping_get_ns_raw();
		*ts = timekeeper.raw_time;

	} while (read_seqretry(&timekeeper.lock, seq));

	timespec_add_ns(ts, nsecs);
}
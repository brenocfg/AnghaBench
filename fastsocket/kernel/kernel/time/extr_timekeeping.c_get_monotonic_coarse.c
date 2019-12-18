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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_2__ {struct timespec wall_to_monotonic; struct timespec xtime; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_normalized_timespec (struct timespec*,scalar_t__,scalar_t__) ; 
 TYPE_1__ timekeeper ; 

struct timespec get_monotonic_coarse(void)
{
	struct timespec now, mono;
	unsigned long seq;

	do {
		seq = read_seqbegin(&timekeeper.lock);

		now = timekeeper.xtime;
		mono = timekeeper.wall_to_monotonic;
	} while (read_seqretry(&timekeeper.lock, seq));

	set_normalized_timespec(&now, now.tv_sec + mono.tv_sec,
				now.tv_nsec + mono.tv_nsec);
	return now;
}
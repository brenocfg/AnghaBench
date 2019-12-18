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
struct TYPE_2__ {struct timespec xtime; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__ timekeeper ; 

struct timespec current_kernel_time(void)
{
	struct timespec now;
	unsigned long seq;

	do {
		seq = read_seqbegin(&timekeeper.lock);

		now = timekeeper.xtime;
	} while (read_seqretry(&timekeeper.lock, seq));

	return now;
}
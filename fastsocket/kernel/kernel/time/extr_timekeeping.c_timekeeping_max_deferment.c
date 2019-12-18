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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {TYPE_1__* clock; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_idle_ns; } ;

/* Variables and functions */
 unsigned long read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_2__ timekeeper ; 

u64 timekeeping_max_deferment(void)
{
	unsigned long seq;
	u64 ret;
	do {
		seq = read_seqbegin(&timekeeper.lock);

		ret = timekeeper.clock->max_idle_ns;

	} while (read_seqretry(&timekeeper.lock, seq));

	return ret;
}
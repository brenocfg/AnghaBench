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
struct percpu_counter {int /*<<< orphan*/  lock; scalar_t__ count; int /*<<< orphan*/  counters; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int get_cpu () ; 
 scalar_t__* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __percpu_counter_add(struct percpu_counter *fbc, s64 amount, s32 batch)
{
	s64 count;
	s32 *pcount;
	int cpu = get_cpu();

	pcount = per_cpu_ptr(fbc->counters, cpu);
	count = *pcount + amount;
	if (count >= batch || count <= -batch) {
		spin_lock(&fbc->lock);
		fbc->count += count;
		*pcount = 0;
		spin_unlock(&fbc->lock);
	} else {
		*pcount = count;
	}
	put_cpu();
}
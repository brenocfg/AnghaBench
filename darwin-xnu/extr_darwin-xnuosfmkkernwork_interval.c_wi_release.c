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
typedef  int uint32_t ;
struct work_interval {int /*<<< orphan*/  wi_ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int atomic_fetch_sub_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct work_interval*,int) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

__attribute__((used)) static inline void
wi_release(struct work_interval *work_interval)
{
	uint32_t old_count;
	old_count = atomic_fetch_sub_explicit(&work_interval->wi_ref_count,
	                                      1, memory_order_relaxed);
	assert(old_count > 0);

	if (old_count == 1) {


		kfree(work_interval, sizeof(struct work_interval));
	}
}
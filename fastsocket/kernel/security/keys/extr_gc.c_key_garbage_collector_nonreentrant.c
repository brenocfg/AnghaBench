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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_garbage_collector (struct work_struct*) ; 
 int /*<<< orphan*/  key_gc_work ; 
 int key_need_gc ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ xchg (unsigned long*,int) ; 

__attribute__((used)) static void key_garbage_collector_nonreentrant(struct work_struct *work)
{
	static unsigned long running;

	if (!key_need_gc)
		return;

	if (xchg(&running, 1) == 0) {
		key_need_gc = false;
		smp_mb();
		key_garbage_collector(work);

		running = 0;
		if (key_need_gc)
			schedule_work(&key_gc_work);
	}
}
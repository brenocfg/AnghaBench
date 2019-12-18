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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  sync_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
task_exit_notify(struct notifier_block *self, unsigned long val, void *data)
{
	/* To avoid latency problems, we only process the current CPU,
	 * hoping that most samples for the task are on this CPU
	 */
	sync_buffer(raw_smp_processor_id());
	return 0;
}
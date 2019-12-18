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
struct ring_buffer_per_cpu {int /*<<< orphan*/  committing; int /*<<< orphan*/  commits; } ;

/* Variables and functions */
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,int) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  local_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_inc (int /*<<< orphan*/ *) ; 
 unsigned long local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_set_commit_to_write (struct ring_buffer_per_cpu*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rb_end_commit(struct ring_buffer_per_cpu *cpu_buffer)
{
	unsigned long commits;

	if (RB_WARN_ON(cpu_buffer,
		       !local_read(&cpu_buffer->committing)))
		return;

 again:
	commits = local_read(&cpu_buffer->commits);
	/* synchronize with interrupts */
	barrier();
	if (local_read(&cpu_buffer->committing) == 1)
		rb_set_commit_to_write(cpu_buffer);

	local_dec(&cpu_buffer->committing);

	/* synchronize with interrupts */
	barrier();

	/*
	 * Need to account for interrupts coming in between the
	 * updating of the commit page and the clearing of the
	 * committing counter.
	 */
	if (unlikely(local_read(&cpu_buffer->commits) != commits) &&
	    !local_read(&cpu_buffer->committing)) {
		local_inc(&cpu_buffer->committing);
		goto again;
	}
}
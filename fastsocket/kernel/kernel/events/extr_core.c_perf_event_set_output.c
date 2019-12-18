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
struct ring_buffer {int dummy; } ;
struct perf_event {int cpu; scalar_t__ ctx; int /*<<< orphan*/  mmap_mutex; struct ring_buffer* rb; int /*<<< orphan*/  mmap_count; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct ring_buffer*,struct ring_buffer*) ; 
 int /*<<< orphan*/  ring_buffer_detach (struct perf_event*,struct ring_buffer*) ; 
 struct ring_buffer* ring_buffer_get (struct perf_event*) ; 
 int /*<<< orphan*/  ring_buffer_put (struct ring_buffer*) ; 

__attribute__((used)) static int
perf_event_set_output(struct perf_event *event, struct perf_event *output_event)
{
	struct ring_buffer *rb = NULL, *old_rb = NULL;
	int ret = -EINVAL;

	if (!output_event)
		goto set;

	/* don't allow circular references */
	if (event == output_event)
		goto out;

	/*
	 * Don't allow cross-cpu buffers
	 */
	if (output_event->cpu != event->cpu)
		goto out;

	/*
	 * If its not a per-cpu rb, it must be the same task.
	 */
	if (output_event->cpu == -1 && output_event->ctx != event->ctx)
		goto out;

set:
	mutex_lock(&event->mmap_mutex);
	/* Can't redirect output if we've got an active mmap() */
	if (atomic_read(&event->mmap_count))
		goto unlock;

	if (output_event) {
		/* get the rb we want to redirect to */
		rb = ring_buffer_get(output_event);
		if (!rb)
			goto unlock;
	}

	old_rb = event->rb;
	rcu_assign_pointer(event->rb, rb);
	if (old_rb)
		ring_buffer_detach(event, old_rb);
	ret = 0;
unlock:
	mutex_unlock(&event->mmap_mutex);

	if (old_rb)
		ring_buffer_put(old_rb);
out:
	return ret;
}
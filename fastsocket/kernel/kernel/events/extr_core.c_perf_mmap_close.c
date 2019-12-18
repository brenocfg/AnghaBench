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
struct vm_area_struct {TYPE_1__* vm_mm; TYPE_2__* vm_file; } ;
struct user_struct {int /*<<< orphan*/  locked_vm; } ;
struct ring_buffer {int dummy; } ;
struct perf_event {int /*<<< orphan*/  mmap_mutex; struct ring_buffer* rb; scalar_t__ mmap_locked; struct user_struct* mmap_user; int /*<<< orphan*/  mmap_count; } ;
struct TYPE_4__ {struct perf_event* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  locked_vm; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ atomic_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_sub (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_uid (struct user_struct*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long perf_data_size (struct ring_buffer*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct ring_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_detach (struct perf_event*,struct ring_buffer*) ; 
 int /*<<< orphan*/  ring_buffer_put (struct ring_buffer*) ; 

__attribute__((used)) static void perf_mmap_close(struct vm_area_struct *vma)
{
	struct perf_event *event = vma->vm_file->private_data;

	if (atomic_dec_and_mutex_lock(&event->mmap_count, &event->mmap_mutex)) {
		unsigned long size = perf_data_size(event->rb);
		struct user_struct *user = event->mmap_user;
		struct ring_buffer *rb = event->rb;

		atomic_long_sub((size >> PAGE_SHIFT) + 1, &user->locked_vm);
		vma->vm_mm->locked_vm -= event->mmap_locked;
		rcu_assign_pointer(event->rb, NULL);
		ring_buffer_detach(event, rb);
		mutex_unlock(&event->mmap_mutex);

		ring_buffer_put(rb);
		free_uid(user);
	}
}
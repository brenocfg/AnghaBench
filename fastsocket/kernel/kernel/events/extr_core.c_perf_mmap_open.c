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
struct vm_area_struct {TYPE_1__* vm_file; } ;
struct perf_event {int /*<<< orphan*/  mmap_count; } ;
struct TYPE_2__ {struct perf_event* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_mmap_open(struct vm_area_struct *vma)
{
	struct perf_event *event = vma->vm_file->private_data;

	atomic_inc(&event->mmap_count);
}
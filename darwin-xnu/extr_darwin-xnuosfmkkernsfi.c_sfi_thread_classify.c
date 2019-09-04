#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ task_t ;
typedef  int /*<<< orphan*/  sfi_class_id_t ;
typedef  int boolean_t ;
struct TYPE_3__ {scalar_t__ task; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFI_CLASS_KERNEL ; 
 int /*<<< orphan*/  SFI_CLASS_OPTED_OUT ; 
 scalar_t__ kernel_task ; 

sfi_class_id_t sfi_thread_classify(thread_t thread)
{
	task_t task = thread->task;
	boolean_t is_kernel_thread = (task == kernel_task);

	if (is_kernel_thread) {
		return SFI_CLASS_KERNEL;
	}

	return SFI_CLASS_OPTED_OUT;
}
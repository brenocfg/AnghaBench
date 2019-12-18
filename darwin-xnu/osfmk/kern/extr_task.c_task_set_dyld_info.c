#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;
struct TYPE_5__ {int /*<<< orphan*/  all_image_info_size; int /*<<< orphan*/  all_image_info_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

void
task_set_dyld_info(
    task_t task, 
    mach_vm_address_t addr, 
    mach_vm_size_t size)
{
	task_lock(task);
	task->all_image_info_addr = addr;
	task->all_image_info_size = size;    
    task_unlock(task);
}
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
struct radeon_vm {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lru_vm; } ;
struct radeon_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

void radeon_vm_add_to_lru(struct radeon_device *rdev, struct radeon_vm *vm)
{
	list_del_init(&vm->list);
	list_add_tail(&vm->list, &rdev->vm_manager.lru_vm);
}
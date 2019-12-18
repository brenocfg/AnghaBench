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
struct radeon_vm {int /*<<< orphan*/  va; int /*<<< orphan*/  list; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * fence; scalar_t__ id; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void radeon_vm_init(struct radeon_device *rdev, struct radeon_vm *vm)
{
	vm->id = 0;
	vm->fence = NULL;
	mutex_init(&vm->mutex);
	INIT_LIST_HEAD(&vm->list);
	INIT_LIST_HEAD(&vm->va);
}
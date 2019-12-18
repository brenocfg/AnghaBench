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
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * cls; } ;
struct memory_block {TYPE_1__ sysdev; int /*<<< orphan*/  start_phys_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  memory_sysdev_class ; 
 int sysdev_register (TYPE_1__*) ; 

__attribute__((used)) static
int register_memory(struct memory_block *memory)
{
	int error;

	memory->sysdev.cls = &memory_sysdev_class;
	memory->sysdev.id = memory->start_phys_index;

	error = sysdev_register(&memory->sysdev);
	return error;
}
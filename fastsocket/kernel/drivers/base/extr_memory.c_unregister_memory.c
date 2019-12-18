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
struct TYPE_2__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/ * cls; } ;
struct memory_block {TYPE_1__ sysdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_sysdev_class ; 
 int /*<<< orphan*/  sysdev_unregister (TYPE_1__*) ; 

__attribute__((used)) static void
unregister_memory(struct memory_block *memory)
{
	BUG_ON(memory->sysdev.cls != &memory_sysdev_class);

	/* drop the ref. we got in remove_memory_block() */
	kobject_put(&memory->sysdev.kobj);
	sysdev_unregister(&memory->sysdev);
}
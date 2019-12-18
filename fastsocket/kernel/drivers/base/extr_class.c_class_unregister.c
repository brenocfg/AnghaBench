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
struct class {TYPE_1__* p; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  class_subsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  kset_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_class_attrs (struct class*) ; 

void class_unregister(struct class *cls)
{
	pr_debug("device class '%s': unregistering\n", cls->name);
	remove_class_attrs(cls);
	kset_unregister(&cls->p->class_subsys);
}
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
struct class {TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  class_subsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  kset_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void class_put(struct class *cls)
{
	if (cls)
		kset_put(&cls->p->class_subsys);
}
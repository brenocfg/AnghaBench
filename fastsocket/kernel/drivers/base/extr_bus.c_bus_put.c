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
struct bus_type {TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  subsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  kset_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bus_put(struct bus_type *bus)
{
	if (bus)
		kset_put(&bus->p->subsys);
}
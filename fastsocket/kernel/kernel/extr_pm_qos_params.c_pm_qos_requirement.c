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
struct TYPE_2__ {int /*<<< orphan*/  target_value; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__** pm_qos_array ; 

int pm_qos_requirement(int pm_qos_class)
{
	return atomic_read(&pm_qos_array[pm_qos_class]->target_value);
}
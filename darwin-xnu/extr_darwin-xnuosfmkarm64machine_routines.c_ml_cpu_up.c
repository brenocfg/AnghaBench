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
struct TYPE_2__ {int /*<<< orphan*/  logical_cpu; int /*<<< orphan*/  physical_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_atomic_add (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ machine_info ; 

void
ml_cpu_up(void)
{
	hw_atomic_add(&machine_info.physical_cpu, 1);
	hw_atomic_add(&machine_info.logical_cpu, 1);
}
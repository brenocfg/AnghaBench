#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ipc_kobject_t ;
typedef  TYPE_1__* clock_t ;
struct TYPE_3__ {int /*<<< orphan*/  cl_control; int /*<<< orphan*/  cl_service; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_CLOCK ; 
 int /*<<< orphan*/  IKOT_CLOCK_CTRL ; 
 int /*<<< orphan*/  ipc_kobject_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_clock_enable(
	clock_t		clock)
{
	ipc_kobject_set(clock->cl_service,
			(ipc_kobject_t) clock, IKOT_CLOCK);
	ipc_kobject_set(clock->cl_control,
			(ipc_kobject_t) clock, IKOT_CLOCK_CTRL);
}
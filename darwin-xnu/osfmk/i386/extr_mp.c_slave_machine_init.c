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

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 void* FULL_SLAVE_INIT ; 
 int /*<<< orphan*/  clock_init () ; 
 int /*<<< orphan*/  cpu_machine_init () ; 
 int /*<<< orphan*/  get_cpu_number () ; 

void
slave_machine_init(void *param)
{
	/*
 	 * Here in process context, but with interrupts disabled.
	 */
	DBG("slave_machine_init() CPU%d\n", get_cpu_number());

	if (param == FULL_SLAVE_INIT) {
		/*
		 * Cold start
		 */
		clock_init();
	}
	cpu_machine_init();	/* Interrupts enabled hereafter */
}
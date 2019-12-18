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
 int /*<<< orphan*/  pet_idle_rate ; 
 int /*<<< orphan*/  pet_sample_all_tasks (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pet_thread_work_unit(void)
{
	pet_sample_all_tasks(pet_idle_rate);
}
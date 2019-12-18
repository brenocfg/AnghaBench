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
typedef  int /*<<< orphan*/  atm_task_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  atm_task_desc_reference_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atm_descriptor_get_reference(atm_task_descriptor_t task_descriptor)
{
	atm_task_desc_reference_internal(task_descriptor);
}
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
 int /*<<< orphan*/  get_input_dev (void*) ; 
 int /*<<< orphan*/  input_mt_report_pointer_emulation (int /*<<< orphan*/ ,int) ; 

void wacom_mt_report_pointer_emulation(void *wcombo, bool value)
{
	input_mt_report_pointer_emulation(get_input_dev(wcombo), value);
}
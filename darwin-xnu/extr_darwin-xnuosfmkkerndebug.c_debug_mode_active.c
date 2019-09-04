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
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ kernel_debugger_entry_count ; 
 scalar_t__ not_in_kdp ; 

boolean_t
debug_mode_active(void)
{
	return ((0 != kernel_debugger_entry_count != 0)	|| (0 == not_in_kdp));
}
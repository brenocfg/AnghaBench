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
 scalar_t__ MAX_SCS_INCREMENT ; 
 int /*<<< orphan*/  current_max_scs ; 
 int /*<<< orphan*/  num_reallocs ; 
 int /*<<< orphan*/  reallocate_char_ptr_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reallocate_integer_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scbol ; 
 int /*<<< orphan*/  sceof ; 
 int /*<<< orphan*/  scname ; 
 int /*<<< orphan*/  scset ; 
 int /*<<< orphan*/  scxclu ; 

void    scextend ()
{
	current_max_scs += MAX_SCS_INCREMENT;

	++num_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_integer_array (scxclu, current_max_scs);
	sceof = reallocate_integer_array (sceof, current_max_scs);
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}
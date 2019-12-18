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
 int /*<<< orphan*/  bp_catch_load ; 
 int /*<<< orphan*/  solib_load_unload_1 (char*,int,char*,char*,int /*<<< orphan*/ ) ; 

void
create_solib_load_event_breakpoint (char *hookname, int tempflag,
				    char *dll_pathname, char *cond_string)
{
  solib_load_unload_1 (hookname, tempflag, dll_pathname, 
		       cond_string, bp_catch_load);
}
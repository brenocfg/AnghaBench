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
 int /*<<< orphan*/  string_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * subsystem_fullpaths ; 

void path_deinit_subsystem(void)
{
   if (subsystem_fullpaths)
      string_list_free(subsystem_fullpaths);
   subsystem_fullpaths = NULL;
}
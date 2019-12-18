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
 int current_display_number ; 
 int /*<<< orphan*/  disable_display (int) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdb_stderr ; 

void
disable_current_display (void)
{
  if (current_display_number >= 0)
    {
      disable_display (current_display_number);
      fprintf_unfiltered (gdb_stderr, "Disabling display %d to avoid infinite recursion.\n",
			  current_display_number);
    }
  current_display_number = -1;
}
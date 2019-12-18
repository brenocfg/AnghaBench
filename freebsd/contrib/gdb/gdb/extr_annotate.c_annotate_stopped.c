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
 int /*<<< orphan*/  annotate_stopped_hook () ; 
 int annotation_level ; 
 int /*<<< orphan*/  breakpoints_changed () ; 
 scalar_t__ ignore_count_changed ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 

void
annotate_stopped (void)
{
  if (annotate_stopped_hook)
    annotate_stopped_hook ();
  else
    {
      if (annotation_level > 1)
	printf_filtered ("\n\032\032stopped\n");
    }
  if (annotation_level > 1 && ignore_count_changed)
    {
      ignore_count_changed = 0;
      breakpoints_changed ();
    }
}
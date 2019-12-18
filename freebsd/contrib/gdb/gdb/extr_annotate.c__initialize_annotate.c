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
 int annotation_level ; 
 void* breakpoint_changed ; 
 void* delete_breakpoint_hook ; 
 void* modify_breakpoint_hook ; 

void
_initialize_annotate (void)
{
  if (annotation_level > 1)
    {
      delete_breakpoint_hook = breakpoint_changed;
      modify_breakpoint_hook = breakpoint_changed;
    }
}
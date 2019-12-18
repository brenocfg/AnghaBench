#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  section; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* debug_displays ; 
 size_t info ; 
 scalar_t__ last_pointer_size ; 
 scalar_t__ load_debug_section (size_t,void*) ; 
 scalar_t__ num_debug_info_entries ; 
 scalar_t__ process_debug_info (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  warned_about_missing_comp_units ; 

__attribute__((used)) static unsigned int
load_debug_info (void * file)
{
  /* Reset the last pointer size so that we can issue correct error
     messages if we are displaying the contents of more than one section.  */
  last_pointer_size = 0;
  warned_about_missing_comp_units = FALSE;

  /* If we already have the information there is nothing else to do.  */
  if (num_debug_info_entries > 0)
    return num_debug_info_entries;

  if (load_debug_section (info, file)
      && process_debug_info (&debug_displays [info].section, file, 1))
    return num_debug_info_entries;
  else
    return 0;
}
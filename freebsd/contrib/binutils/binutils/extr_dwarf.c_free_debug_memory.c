#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum dwarf_section_display_enum { ____Placeholder_dwarf_section_display_enum } dwarf_section_display_enum ;
struct TYPE_3__ {struct TYPE_3__* range_lists; int /*<<< orphan*/  max_range_lists; struct TYPE_3__* have_frame_base; struct TYPE_3__* loc_offsets; int /*<<< orphan*/  max_loc_offsets; } ;

/* Variables and functions */
 TYPE_1__* debug_information ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_abbrevs () ; 
 int /*<<< orphan*/  free_debug_section (int) ; 
 int max ; 
 int num_debug_info_entries ; 

void
free_debug_memory (void)
{
  enum dwarf_section_display_enum i;

  free_abbrevs ();

  for (i = 0; i < max; i++)
    free_debug_section (i);

  if (debug_information)
    {
      for (i = 0; i < num_debug_info_entries; i++)
	{
	  if (!debug_information [i].max_loc_offsets)
	    {
	      free (debug_information [i].loc_offsets);
	      free (debug_information [i].have_frame_base);
	    }
	  if (!debug_information [i].max_range_lists)
	    free (debug_information [i].range_lists);
	}
      free (debug_information);
      debug_information = NULL;
      num_debug_info_entries = 0;
    }

}
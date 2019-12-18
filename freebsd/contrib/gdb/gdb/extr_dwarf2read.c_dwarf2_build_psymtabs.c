#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; } ;
struct TYPE_3__ {scalar_t__ size; } ;
struct objfile {TYPE_2__ static_psymbols; TYPE_1__ global_psymbols; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf2_build_psymtabs_easy (struct objfile*,int) ; 
 int /*<<< orphan*/  dwarf2_build_psymtabs_hard (struct objfile*,int) ; 
 void* dwarf2_read_section (struct objfile*,scalar_t__) ; 
 void* dwarf_abbrev_buffer ; 
 scalar_t__ dwarf_abbrev_section ; 
 scalar_t__ dwarf_aranges_offset ; 
 void* dwarf_info_buffer ; 
 scalar_t__ dwarf_info_section ; 
 int /*<<< orphan*/ * dwarf_line_buffer ; 
 scalar_t__ dwarf_line_section ; 
 int /*<<< orphan*/ * dwarf_loc_buffer ; 
 scalar_t__ dwarf_loc_section ; 
 int /*<<< orphan*/ * dwarf_macinfo_buffer ; 
 scalar_t__ dwarf_macinfo_section ; 
 scalar_t__ dwarf_pubnames_offset ; 
 int /*<<< orphan*/ * dwarf_ranges_buffer ; 
 scalar_t__ dwarf_ranges_section ; 
 int /*<<< orphan*/ * dwarf_str_buffer ; 
 scalar_t__ dwarf_str_section ; 
 int /*<<< orphan*/  init_psymbol_list (struct objfile*,int) ; 

void
dwarf2_build_psymtabs (struct objfile *objfile, int mainline)
{

  /* We definitely need the .debug_info and .debug_abbrev sections */

  dwarf_info_buffer = dwarf2_read_section (objfile, dwarf_info_section);
  dwarf_abbrev_buffer = dwarf2_read_section (objfile, dwarf_abbrev_section);

  if (dwarf_line_section)
    dwarf_line_buffer = dwarf2_read_section (objfile, dwarf_line_section);
  else
    dwarf_line_buffer = NULL;

  if (dwarf_str_section)
    dwarf_str_buffer = dwarf2_read_section (objfile, dwarf_str_section);
  else
    dwarf_str_buffer = NULL;

  if (dwarf_macinfo_section)
    dwarf_macinfo_buffer = dwarf2_read_section (objfile,
						dwarf_macinfo_section);
  else
    dwarf_macinfo_buffer = NULL;

  if (dwarf_ranges_section)
    dwarf_ranges_buffer = dwarf2_read_section (objfile, dwarf_ranges_section);
  else
    dwarf_ranges_buffer = NULL;

  if (dwarf_loc_section)
    dwarf_loc_buffer = dwarf2_read_section (objfile, dwarf_loc_section);
  else
    dwarf_loc_buffer = NULL;

  if (mainline
      || (objfile->global_psymbols.size == 0
	  && objfile->static_psymbols.size == 0))
    {
      init_psymbol_list (objfile, 1024);
    }

#if 0
  if (dwarf_aranges_offset && dwarf_pubnames_offset)
    {
      /* Things are significantly easier if we have .debug_aranges and
         .debug_pubnames sections */

      dwarf2_build_psymtabs_easy (objfile, mainline);
    }
  else
#endif
    /* only test this case for now */
    {
      /* In this case we have to work a bit harder */
      dwarf2_build_psymtabs_hard (objfile, mainline);
    }
}
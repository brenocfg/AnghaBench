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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf2_locate_sections ; 
 int /*<<< orphan*/ * dwarf_abbrev_section ; 
 scalar_t__ dwarf_eh_frame_section ; 
 scalar_t__ dwarf_frame_section ; 
 int /*<<< orphan*/ * dwarf_info_section ; 
 scalar_t__ dwarf_line_section ; 
 scalar_t__ dwarf_loc_section ; 
 scalar_t__ dwarf_macinfo_section ; 
 scalar_t__ dwarf_ranges_section ; 
 scalar_t__ dwarf_str_section ; 

int
dwarf2_has_info (bfd *abfd)
{
  dwarf_info_section = 0;
  dwarf_abbrev_section = 0;
  dwarf_line_section = 0;
  dwarf_str_section = 0;
  dwarf_macinfo_section = 0;
  dwarf_frame_section = 0;
  dwarf_eh_frame_section = 0;
  dwarf_ranges_section = 0;
  dwarf_loc_section = 0;
  
  bfd_map_over_sections (abfd, dwarf2_locate_sections, NULL);
  return (dwarf_info_section != NULL && dwarf_abbrev_section != NULL);
}
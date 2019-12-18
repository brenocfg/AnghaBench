#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  ABBREV_SECTION ; 
 int /*<<< orphan*/  ARANGES_SECTION ; 
 int /*<<< orphan*/  EH_FRAME_SECTION ; 
 int /*<<< orphan*/  FRAME_SECTION ; 
 int /*<<< orphan*/  INFO_SECTION ; 
 int /*<<< orphan*/  LINE_SECTION ; 
 int /*<<< orphan*/  LOC_SECTION ; 
 int /*<<< orphan*/  MACINFO_SECTION ; 
 int /*<<< orphan*/  PUBNAMES_SECTION ; 
 int /*<<< orphan*/  RANGES_SECTION ; 
 int SEC_HAS_CONTENTS ; 
 int /*<<< orphan*/  STR_SECTION ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* bfd_get_section_size (TYPE_1__*) ; 
 TYPE_1__* dwarf_abbrev_section ; 
 void* dwarf_abbrev_size ; 
 TYPE_1__* dwarf_aranges_section ; 
 void* dwarf_aranges_size ; 
 TYPE_1__* dwarf_eh_frame_section ; 
 void* dwarf_eh_frame_size ; 
 TYPE_1__* dwarf_frame_section ; 
 void* dwarf_frame_size ; 
 TYPE_1__* dwarf_info_section ; 
 void* dwarf_info_size ; 
 TYPE_1__* dwarf_line_section ; 
 void* dwarf_line_size ; 
 TYPE_1__* dwarf_loc_section ; 
 void* dwarf_loc_size ; 
 TYPE_1__* dwarf_macinfo_section ; 
 void* dwarf_macinfo_size ; 
 TYPE_1__* dwarf_pubnames_section ; 
 void* dwarf_pubnames_size ; 
 TYPE_1__* dwarf_ranges_section ; 
 void* dwarf_ranges_size ; 
 TYPE_1__* dwarf_str_section ; 
 void* dwarf_str_size ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwarf2_locate_sections (bfd *ignore_abfd, asection *sectp, void *ignore_ptr)
{
  if (strcmp (sectp->name, INFO_SECTION) == 0)
    {
      dwarf_info_size = bfd_get_section_size (sectp);
      dwarf_info_section = sectp;
    }
  else if (strcmp (sectp->name, ABBREV_SECTION) == 0)
    {
      dwarf_abbrev_size = bfd_get_section_size (sectp);
      dwarf_abbrev_section = sectp;
    }
  else if (strcmp (sectp->name, LINE_SECTION) == 0)
    {
      dwarf_line_size = bfd_get_section_size (sectp);
      dwarf_line_section = sectp;
    }
  else if (strcmp (sectp->name, PUBNAMES_SECTION) == 0)
    {
      dwarf_pubnames_size = bfd_get_section_size (sectp);
      dwarf_pubnames_section = sectp;
    }
  else if (strcmp (sectp->name, ARANGES_SECTION) == 0)
    {
      dwarf_aranges_size = bfd_get_section_size (sectp);
      dwarf_aranges_section = sectp;
    }
  else if (strcmp (sectp->name, LOC_SECTION) == 0)
    {
      dwarf_loc_size = bfd_get_section_size (sectp);
      dwarf_loc_section = sectp;
    }
  else if (strcmp (sectp->name, MACINFO_SECTION) == 0)
    {
      dwarf_macinfo_size = bfd_get_section_size (sectp);
      dwarf_macinfo_section = sectp;
    }
  else if (strcmp (sectp->name, STR_SECTION) == 0)
    {
      dwarf_str_size = bfd_get_section_size (sectp);
      dwarf_str_section = sectp;
    }
  else if (strcmp (sectp->name, FRAME_SECTION) == 0)
    {
      dwarf_frame_size = bfd_get_section_size (sectp);
      dwarf_frame_section = sectp;
    }
  else if (strcmp (sectp->name, EH_FRAME_SECTION) == 0)
    {
      flagword aflag = bfd_get_section_flags (ignore_abfd, sectp);
      if (aflag & SEC_HAS_CONTENTS)
        {
          dwarf_eh_frame_size = bfd_get_section_size (sectp);
          dwarf_eh_frame_section = sectp;
        }
    }
  else if (strcmp (sectp->name, RANGES_SECTION) == 0)
    {
      dwarf_ranges_size = bfd_get_section_size (sectp);
      dwarf_ranges_section = sectp;
    }
}
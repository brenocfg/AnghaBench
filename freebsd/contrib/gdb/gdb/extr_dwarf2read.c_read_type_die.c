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
struct dwarf2_cu {int dummy; } ;
struct die_info {int tag; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
#define  DW_TAG_array_type 146 
#define  DW_TAG_base_type 145 
#define  DW_TAG_class_type 144 
#define  DW_TAG_const_type 143 
#define  DW_TAG_enumeration_type 142 
#define  DW_TAG_pointer_type 141 
#define  DW_TAG_ptr_to_member_type 140 
#define  DW_TAG_reference_type 139 
#define  DW_TAG_restrict_type 138 
#define  DW_TAG_rvalue_reference_type 137 
#define  DW_TAG_string_type 136 
#define  DW_TAG_structure_type 135 
#define  DW_TAG_subprogram 134 
#define  DW_TAG_subrange_type 133 
#define  DW_TAG_subroutine_type 132 
#define  DW_TAG_typedef 131 
#define  DW_TAG_union_type 130 
#define  DW_TAG_unspecified_type 129 
#define  DW_TAG_volatile_type 128 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* determine_prefix (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  dwarf_tag_name (int) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 char const* processing_current_prefix ; 
 int /*<<< orphan*/  read_array_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_base_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_enumeration_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_structure_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_subrange_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_subroutine_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_const_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_pointer_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_ptr_to_member_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_reference_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_restrict_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_string_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_unspecified_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_volatile_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_typedef (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
read_type_die (struct die_info *die, struct dwarf2_cu *cu)
{
  char *prefix = determine_prefix (die, cu);
  const char *old_prefix = processing_current_prefix;
  struct cleanup *back_to = make_cleanup (xfree, prefix);
  processing_current_prefix = prefix;
  
  switch (die->tag)
    {
    case DW_TAG_class_type:
    case DW_TAG_structure_type:
    case DW_TAG_union_type:
      read_structure_type (die, cu);
      break;
    case DW_TAG_enumeration_type:
      read_enumeration_type (die, cu);
      break;
    case DW_TAG_subprogram:
    case DW_TAG_subroutine_type:
      read_subroutine_type (die, cu);
      break;
    case DW_TAG_array_type:
      read_array_type (die, cu);
      break;
    case DW_TAG_pointer_type:
      read_tag_pointer_type (die, cu);
      break;
    case DW_TAG_unspecified_type:
      read_tag_unspecified_type (die, cu);
      break;
    case DW_TAG_ptr_to_member_type:
      read_tag_ptr_to_member_type (die, cu);
      break;
    case DW_TAG_reference_type:
    case DW_TAG_rvalue_reference_type:
      read_tag_reference_type (die, cu);
      break;
    case DW_TAG_const_type:
      read_tag_const_type (die, cu);
      break;
    case DW_TAG_volatile_type:
      read_tag_volatile_type (die, cu);
      break;
    case DW_TAG_restrict_type:
      read_tag_restrict_type (die, cu);
      break;
    case DW_TAG_string_type:
      read_tag_string_type (die, cu);
      break;
    case DW_TAG_typedef:
      read_typedef (die, cu);
      break;
    case DW_TAG_subrange_type:
      read_subrange_type (die, cu);
      break;
    case DW_TAG_base_type:
      read_base_type (die, cu);
      break;
    default:
      complaint (&symfile_complaints, "unexepected tag in read_type_die: '%s'",
		 dwarf_tag_name (die->tag));
      break;
    }

  processing_current_prefix = old_prefix;
  do_cleanups (back_to);
}
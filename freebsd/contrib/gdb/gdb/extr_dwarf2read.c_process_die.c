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
struct die_info {int tag; int /*<<< orphan*/ * child; int /*<<< orphan*/ * type; } ;

/* Variables and functions */
#define  DW_TAG_array_type 152 
#define  DW_TAG_base_type 151 
#define  DW_TAG_catch_block 150 
#define  DW_TAG_class_type 149 
#define  DW_TAG_common_block 148 
#define  DW_TAG_common_inclusion 147 
#define  DW_TAG_compile_unit 146 
#define  DW_TAG_enumeration_type 145 
#define  DW_TAG_imported_declaration 144 
#define  DW_TAG_imported_module 143 
#define  DW_TAG_inlined_subroutine 142 
#define  DW_TAG_lexical_block 141 
#define  DW_TAG_namespace 140 
#define  DW_TAG_padding 139 
#define  DW_TAG_pointer_type 138 
#define  DW_TAG_ptr_to_member_type 137 
#define  DW_TAG_reference_type 136 
#define  DW_TAG_rvalue_reference_type 135 
#define  DW_TAG_string_type 134 
#define  DW_TAG_structure_type 133 
#define  DW_TAG_subprogram 132 
#define  DW_TAG_subrange_type 131 
#define  DW_TAG_subroutine_type 130 
#define  DW_TAG_try_block 129 
#define  DW_TAG_union_type 128 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_symbol (struct die_info*,int /*<<< orphan*/ *,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  process_enumeration_scope (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  process_structure_scope (struct die_info*,struct dwarf2_cu*) ; 
 int processing_has_namespace_info ; 
 int /*<<< orphan*/  read_array_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_base_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_common_block (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_enumeration_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_file_scope (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_func_scope (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_lexical_block_scope (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_namespace (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_structure_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_subrange_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_subroutine_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_pointer_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_ptr_to_member_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_reference_type (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  read_tag_string_type (struct die_info*,struct dwarf2_cu*) ; 

__attribute__((used)) static void
process_die (struct die_info *die, struct dwarf2_cu *cu)
{
  switch (die->tag)
    {
    case DW_TAG_padding:
      break;
    case DW_TAG_compile_unit:
      read_file_scope (die, cu);
      break;
    case DW_TAG_subprogram:
      read_subroutine_type (die, cu);
      read_func_scope (die, cu);
      break;
    case DW_TAG_inlined_subroutine:
      /* FIXME:  These are ignored for now.
         They could be used to set breakpoints on all inlined instances
         of a function and make GDB `next' properly over inlined functions.  */
      break;
    case DW_TAG_lexical_block:
    case DW_TAG_try_block:
    case DW_TAG_catch_block:
      read_lexical_block_scope (die, cu);
      break;
    case DW_TAG_class_type:
    case DW_TAG_structure_type:
    case DW_TAG_union_type:
      read_structure_type (die, cu);
      process_structure_scope (die, cu);
      break;
    case DW_TAG_enumeration_type:
      read_enumeration_type (die, cu);
      process_enumeration_scope (die, cu);
      break;

    /* FIXME drow/2004-03-14: These initialize die->type, but do not create
       a symbol or process any children.  Therefore it doesn't do anything
       that won't be done on-demand by read_type_die.  */
    case DW_TAG_subroutine_type:
      read_subroutine_type (die, cu);
      break;
    case DW_TAG_array_type:
      read_array_type (die, cu);
      break;
    case DW_TAG_pointer_type:
      read_tag_pointer_type (die, cu);
      break;
    case DW_TAG_ptr_to_member_type:
      read_tag_ptr_to_member_type (die, cu);
      break;
    case DW_TAG_reference_type:
    case DW_TAG_rvalue_reference_type:
      read_tag_reference_type (die, cu);
      break;
    case DW_TAG_string_type:
      read_tag_string_type (die, cu);
      break;
    /* END FIXME */

    case DW_TAG_base_type:
      read_base_type (die, cu);
      /* Add a typedef symbol for the type definition, if it has a
	 DW_AT_name.  */
      new_symbol (die, die->type, cu);
      break;
    case DW_TAG_subrange_type:
      read_subrange_type (die, cu);
      /* Add a typedef symbol for the type definition, if it has a
         DW_AT_name.  */
      new_symbol (die, die->type, cu);
      break;
    case DW_TAG_common_block:
      read_common_block (die, cu);
      break;
    case DW_TAG_common_inclusion:
      break;
    case DW_TAG_namespace:
      processing_has_namespace_info = 1;
      read_namespace (die, cu);
      break;
    case DW_TAG_imported_declaration:
    case DW_TAG_imported_module:
      /* FIXME: carlton/2002-10-16: Eventually, we should use the
	 information contained in these.  DW_TAG_imported_declaration
	 dies shouldn't have children; DW_TAG_imported_module dies
	 shouldn't in the C++ case, but conceivably could in the
	 Fortran case, so we'll have to replace this gdb_assert if
	 Fortran compilers start generating that info.  */
      processing_has_namespace_info = 1;
      gdb_assert (die->child == NULL);
      break;
    default:
      new_symbol (die, NULL, cu);
      break;
    }
}
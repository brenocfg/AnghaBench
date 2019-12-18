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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
#define  DW_TAG_MIPS_loop 190 
#define  DW_TAG_access_declaration 189 
#define  DW_TAG_array_type 188 
#define  DW_TAG_base_type 187 
#define  DW_TAG_catch_block 186 
#define  DW_TAG_class_template 185 
#define  DW_TAG_class_type 184 
#define  DW_TAG_common_block 183 
#define  DW_TAG_common_inclusion 182 
#define  DW_TAG_compile_unit 181 
#define  DW_TAG_const_type 180 
#define  DW_TAG_constant 179 
#define  DW_TAG_dwarf_procedure 178 
#define  DW_TAG_entry_point 177 
#define  DW_TAG_enumeration_type 176 
#define  DW_TAG_enumerator 175 
#define  DW_TAG_file_type 174 
#define  DW_TAG_formal_parameter 173 
#define  DW_TAG_format_label 172 
#define  DW_TAG_friend 171 
#define  DW_TAG_function_template 170 
#define  DW_TAG_imported_declaration 169 
#define  DW_TAG_imported_module 168 
#define  DW_TAG_imported_unit 167 
#define  DW_TAG_inheritance 166 
#define  DW_TAG_inlined_subroutine 165 
#define  DW_TAG_interface_type 164 
#define  DW_TAG_label 163 
#define  DW_TAG_lexical_block 162 
#define  DW_TAG_member 161 
#define  DW_TAG_module 160 
#define  DW_TAG_namelist 159 
#define  DW_TAG_namelist_item 158 
#define  DW_TAG_namespace 157 
#define  DW_TAG_packed_type 156 
#define  DW_TAG_padding 155 
#define  DW_TAG_partial_unit 154 
#define  DW_TAG_pointer_type 153 
#define  DW_TAG_ptr_to_member_type 152 
#define  DW_TAG_reference_type 151 
#define  DW_TAG_restrict_type 150 
#define  DW_TAG_set_type 149 
#define  DW_TAG_string_type 148 
#define  DW_TAG_structure_type 147 
#define  DW_TAG_subprogram 146 
#define  DW_TAG_subrange_type 145 
#define  DW_TAG_subroutine_type 144 
#define  DW_TAG_template_type_param 143 
#define  DW_TAG_template_value_param 142 
#define  DW_TAG_thrown_type 141 
#define  DW_TAG_try_block 140 
#define  DW_TAG_typedef 139 
#define  DW_TAG_union_type 138 
#define  DW_TAG_unspecified_parameters 137 
#define  DW_TAG_unspecified_type 136 
#define  DW_TAG_upc_relaxed_type 135 
#define  DW_TAG_upc_shared_type 134 
#define  DW_TAG_upc_strict_type 133 
#define  DW_TAG_variable 132 
#define  DW_TAG_variant 131 
#define  DW_TAG_variant_part 130 
#define  DW_TAG_volatile_type 129 
#define  DW_TAG_with_stmt 128 
 char* _ (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 

__attribute__((used)) static char *
get_TAG_name (unsigned long tag)
{
  switch (tag)
    {
    case DW_TAG_padding:		return "DW_TAG_padding";
    case DW_TAG_array_type:		return "DW_TAG_array_type";
    case DW_TAG_class_type:		return "DW_TAG_class_type";
    case DW_TAG_entry_point:		return "DW_TAG_entry_point";
    case DW_TAG_enumeration_type:	return "DW_TAG_enumeration_type";
    case DW_TAG_formal_parameter:	return "DW_TAG_formal_parameter";
    case DW_TAG_imported_declaration:	return "DW_TAG_imported_declaration";
    case DW_TAG_label:			return "DW_TAG_label";
    case DW_TAG_lexical_block:		return "DW_TAG_lexical_block";
    case DW_TAG_member:			return "DW_TAG_member";
    case DW_TAG_pointer_type:		return "DW_TAG_pointer_type";
    case DW_TAG_reference_type:		return "DW_TAG_reference_type";
    case DW_TAG_compile_unit:		return "DW_TAG_compile_unit";
    case DW_TAG_string_type:		return "DW_TAG_string_type";
    case DW_TAG_structure_type:		return "DW_TAG_structure_type";
    case DW_TAG_subroutine_type:	return "DW_TAG_subroutine_type";
    case DW_TAG_typedef:		return "DW_TAG_typedef";
    case DW_TAG_union_type:		return "DW_TAG_union_type";
    case DW_TAG_unspecified_parameters: return "DW_TAG_unspecified_parameters";
    case DW_TAG_variant:		return "DW_TAG_variant";
    case DW_TAG_common_block:		return "DW_TAG_common_block";
    case DW_TAG_common_inclusion:	return "DW_TAG_common_inclusion";
    case DW_TAG_inheritance:		return "DW_TAG_inheritance";
    case DW_TAG_inlined_subroutine:	return "DW_TAG_inlined_subroutine";
    case DW_TAG_module:			return "DW_TAG_module";
    case DW_TAG_ptr_to_member_type:	return "DW_TAG_ptr_to_member_type";
    case DW_TAG_set_type:		return "DW_TAG_set_type";
    case DW_TAG_subrange_type:		return "DW_TAG_subrange_type";
    case DW_TAG_with_stmt:		return "DW_TAG_with_stmt";
    case DW_TAG_access_declaration:	return "DW_TAG_access_declaration";
    case DW_TAG_base_type:		return "DW_TAG_base_type";
    case DW_TAG_catch_block:		return "DW_TAG_catch_block";
    case DW_TAG_const_type:		return "DW_TAG_const_type";
    case DW_TAG_constant:		return "DW_TAG_constant";
    case DW_TAG_enumerator:		return "DW_TAG_enumerator";
    case DW_TAG_file_type:		return "DW_TAG_file_type";
    case DW_TAG_friend:			return "DW_TAG_friend";
    case DW_TAG_namelist:		return "DW_TAG_namelist";
    case DW_TAG_namelist_item:		return "DW_TAG_namelist_item";
    case DW_TAG_packed_type:		return "DW_TAG_packed_type";
    case DW_TAG_subprogram:		return "DW_TAG_subprogram";
    case DW_TAG_template_type_param:	return "DW_TAG_template_type_param";
    case DW_TAG_template_value_param:	return "DW_TAG_template_value_param";
    case DW_TAG_thrown_type:		return "DW_TAG_thrown_type";
    case DW_TAG_try_block:		return "DW_TAG_try_block";
    case DW_TAG_variant_part:		return "DW_TAG_variant_part";
    case DW_TAG_variable:		return "DW_TAG_variable";
    case DW_TAG_volatile_type:		return "DW_TAG_volatile_type";
    case DW_TAG_MIPS_loop:		return "DW_TAG_MIPS_loop";
    case DW_TAG_format_label:		return "DW_TAG_format_label";
    case DW_TAG_function_template:	return "DW_TAG_function_template";
    case DW_TAG_class_template:		return "DW_TAG_class_template";
      /* DWARF 2.1 values.  */
    case DW_TAG_dwarf_procedure:	return "DW_TAG_dwarf_procedure";
    case DW_TAG_restrict_type:		return "DW_TAG_restrict_type";
    case DW_TAG_interface_type:		return "DW_TAG_interface_type";
    case DW_TAG_namespace:		return "DW_TAG_namespace";
    case DW_TAG_imported_module:	return "DW_TAG_imported_module";
    case DW_TAG_unspecified_type:	return "DW_TAG_unspecified_type";
    case DW_TAG_partial_unit:		return "DW_TAG_partial_unit";
    case DW_TAG_imported_unit:		return "DW_TAG_imported_unit";
      /* UPC values.  */
    case DW_TAG_upc_shared_type:	return "DW_TAG_upc_shared_type";
    case DW_TAG_upc_strict_type:	return "DW_TAG_upc_strict_type";
    case DW_TAG_upc_relaxed_type:	return "DW_TAG_upc_relaxed_type";
    default:
      {
	static char buffer[100];

	snprintf (buffer, sizeof (buffer), _("Unknown TAG value: %lx"), tag);
	return buffer;
      }
    }
}
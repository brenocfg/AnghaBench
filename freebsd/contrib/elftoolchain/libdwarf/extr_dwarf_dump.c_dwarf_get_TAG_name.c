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
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
#define  DW_TAG_GNU_BINCL 196 
#define  DW_TAG_GNU_EINCL 195 
#define  DW_TAG_GNU_call_site 194 
#define  DW_TAG_GNU_call_site_parameter 193 
#define  DW_TAG_GNU_formal_parameter_pack 192 
#define  DW_TAG_GNU_template_parameter_pack 191 
#define  DW_TAG_GNU_template_template_param 190 
#define  DW_TAG_access_declaration 189 
#define  DW_TAG_array_type 188 
#define  DW_TAG_base_type 187 
#define  DW_TAG_catch_block 186 
#define  DW_TAG_class_template 185 
#define  DW_TAG_class_type 184 
#define  DW_TAG_common_block 183 
#define  DW_TAG_common_inclusion 182 
#define  DW_TAG_compile_unit 181 
#define  DW_TAG_condition 180 
#define  DW_TAG_const_type 179 
#define  DW_TAG_constant 178 
#define  DW_TAG_dwarf_procedure 177 
#define  DW_TAG_entry_point 176 
#define  DW_TAG_enumeration_type 175 
#define  DW_TAG_enumerator 174 
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
#define  DW_TAG_partial_unit 155 
#define  DW_TAG_pointer_type 154 
#define  DW_TAG_ptr_to_member_type 153 
#define  DW_TAG_reference_type 152 
#define  DW_TAG_restrict_type 151 
#define  DW_TAG_rvalue_reference_type 150 
#define  DW_TAG_set_type 149 
#define  DW_TAG_shared_type 148 
#define  DW_TAG_string_type 147 
#define  DW_TAG_structure_type 146 
#define  DW_TAG_subprogram 145 
#define  DW_TAG_subrange_type 144 
#define  DW_TAG_subroutine_type 143 
#define  DW_TAG_template_alias 142 
#define  DW_TAG_template_type_parameter 141 
#define  DW_TAG_template_value_parameter 140 
#define  DW_TAG_thrown_type 139 
#define  DW_TAG_try_block 138 
#define  DW_TAG_type_unit 137 
#define  DW_TAG_typedef 136 
#define  DW_TAG_union_type 135 
#define  DW_TAG_unspecified_parameters 134 
#define  DW_TAG_unspecified_type 133 
#define  DW_TAG_variable 132 
#define  DW_TAG_variant 131 
#define  DW_TAG_variant_part 130 
#define  DW_TAG_volatile_type 129 
#define  DW_TAG_with_stmt 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_TAG_name(unsigned tag, const char **s)
{

	assert(s != NULL);

	switch (tag) {
	case DW_TAG_access_declaration:
		*s = "DW_TAG_access_declaration"; break;
	case DW_TAG_array_type:
		*s = "DW_TAG_array_type"; break;
	case DW_TAG_base_type:
		*s = "DW_TAG_base_type"; break;
	case DW_TAG_catch_block:
		*s = "DW_TAG_catch_block"; break;
	case DW_TAG_class_type:
		*s = "DW_TAG_class_type"; break;
	case DW_TAG_common_block:
		*s = "DW_TAG_common_block"; break;
	case DW_TAG_common_inclusion:
		*s = "DW_TAG_common_inclusion"; break;
	case DW_TAG_compile_unit:
		*s = "DW_TAG_compile_unit"; break;
	case DW_TAG_condition:
		*s = "DW_TAG_condition"; break;
	case DW_TAG_const_type:
		*s = "DW_TAG_const_type"; break;
	case DW_TAG_constant:
		*s = "DW_TAG_constant"; break;
	case DW_TAG_dwarf_procedure:
		*s = "DW_TAG_dwarf_procedure"; break;
	case DW_TAG_entry_point:
		*s = "DW_TAG_entry_point"; break;
	case DW_TAG_enumeration_type:
		*s = "DW_TAG_enumeration_type"; break;
	case DW_TAG_enumerator:
		*s = "DW_TAG_enumerator"; break;
	case DW_TAG_formal_parameter:
		*s = "DW_TAG_formal_parameter"; break;
	case DW_TAG_friend:
		*s = "DW_TAG_friend"; break;
	case DW_TAG_imported_declaration:
		*s = "DW_TAG_imported_declaration"; break;
	case DW_TAG_imported_module:
		*s = "DW_TAG_imported_module"; break;
	case DW_TAG_imported_unit:
		*s = "DW_TAG_imported_unit"; break;
	case DW_TAG_inheritance:
		*s = "DW_TAG_inheritance"; break;
	case DW_TAG_inlined_subroutine:
		*s = "DW_TAG_inlined_subroutine"; break;
	case DW_TAG_interface_type:
		*s = "DW_TAG_interface_type"; break;
	case DW_TAG_label:
		*s = "DW_TAG_label"; break;
	case DW_TAG_lexical_block:
		*s = "DW_TAG_lexical_block"; break;
	case DW_TAG_member:
		*s = "DW_TAG_member"; break;
	case DW_TAG_module:
		*s = "DW_TAG_module"; break;
	case DW_TAG_namelist:
		*s = "DW_TAG_namelist"; break;
	case DW_TAG_namelist_item:
		*s = "DW_TAG_namelist_item"; break;
	case DW_TAG_namespace:
		*s = "DW_TAG_namespace"; break;
	case DW_TAG_packed_type:
		*s = "DW_TAG_packed_type"; break;
	case DW_TAG_partial_unit:
		*s = "DW_TAG_partial_unit"; break;
	case DW_TAG_pointer_type:
		*s = "DW_TAG_pointer_type"; break;
	case DW_TAG_ptr_to_member_type:
		*s = "DW_TAG_ptr_to_member_type"; break;
	case DW_TAG_reference_type:
		*s = "DW_TAG_reference_type"; break;
	case DW_TAG_restrict_type:
		*s = "DW_TAG_restrict_type"; break;
	case DW_TAG_rvalue_reference_type:
		*s = "DW_TAG_rvalue_reference_type"; break;
	case DW_TAG_set_type:
		*s = "DW_TAG_set_type"; break;
	case DW_TAG_shared_type:
		*s = "DW_TAG_shared_type"; break;
	case DW_TAG_string_type:
		*s = "DW_TAG_string_type"; break;
	case DW_TAG_structure_type:
		*s = "DW_TAG_structure_type"; break;
	case DW_TAG_subprogram:
		*s = "DW_TAG_subprogram"; break;
	case DW_TAG_subrange_type:
		*s = "DW_TAG_subrange_type"; break;
	case DW_TAG_subroutine_type:
		*s = "DW_TAG_subroutine_type"; break;
	case DW_TAG_template_alias:
		*s = "DW_TAG_template_alias"; break;
	case DW_TAG_template_type_parameter:
		*s = "DW_TAG_template_type_parameter"; break;
	case DW_TAG_template_value_parameter:
		*s = "DW_TAG_template_value_parameter"; break;
	case DW_TAG_thrown_type:
		*s = "DW_TAG_thrown_type"; break;
	case DW_TAG_try_block:
		*s = "DW_TAG_try_block"; break;
	case DW_TAG_type_unit:
		*s = "DW_TAG_type_unit"; break;
	case DW_TAG_typedef:
		*s = "DW_TAG_typedef"; break;
	case DW_TAG_union_type:
		*s = "DW_TAG_union_type"; break;
	case DW_TAG_unspecified_parameters:
		*s = "DW_TAG_unspecified_parameters"; break;
	case DW_TAG_unspecified_type:
		*s = "DW_TAG_unspecified_type"; break;
	case DW_TAG_variable:
		*s = "DW_TAG_variable"; break;
	case DW_TAG_variant:
		*s = "DW_TAG_variant"; break;
	case DW_TAG_variant_part:
		*s = "DW_TAG_variant_part"; break;
	case DW_TAG_volatile_type:
		*s = "DW_TAG_volatile_type"; break;
	case DW_TAG_with_stmt:
		*s = "DW_TAG_with_stmt"; break;
	case DW_TAG_format_label:
		*s = "DW_TAG_format_label"; break;
	case DW_TAG_function_template:
		*s = "DW_TAG_function_template"; break;
	case DW_TAG_class_template:
		*s = "DW_TAG_class_template"; break;
	case DW_TAG_GNU_BINCL:
		*s = "DW_TAG_GNU_BINCL"; break;
	case DW_TAG_GNU_EINCL:
		*s = "DW_TAG_GNU_EINCL"; break;
	case DW_TAG_GNU_template_template_param:
		*s = "DW_TAG_GNU_template_template_param"; break;
	case DW_TAG_GNU_template_parameter_pack:
		*s = "DW_TAG_GNU_template_parameter_pack"; break;
	case DW_TAG_GNU_formal_parameter_pack:
		*s = "DW_TAG_GNU_formal_parameter_pack"; break;
	case DW_TAG_GNU_call_site:
		*s = "DW_TAG_GNU_call_site"; break;
	case DW_TAG_GNU_call_site_parameter:
		*s = "DW_TAG_GNU_call_site_parameter"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}
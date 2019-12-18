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
#define  DW_AT_GNU_vector 215 
#define  DW_AT_MIPS_epilog_begin 214 
#define  DW_AT_MIPS_fde 213 
#define  DW_AT_MIPS_linkage_name 212 
#define  DW_AT_MIPS_loop_begin 211 
#define  DW_AT_MIPS_loop_unroll_factor 210 
#define  DW_AT_MIPS_software_pipeline_depth 209 
#define  DW_AT_MIPS_tail_loop_begin 208 
#define  DW_AT_abstract_origin 207 
#define  DW_AT_accessibility 206 
#define  DW_AT_address_class 205 
#define  DW_AT_allocated 204 
#define  DW_AT_artificial 203 
#define  DW_AT_associated 202 
#define  DW_AT_base_types 201 
#define  DW_AT_bit_offset 200 
#define  DW_AT_bit_size 199 
#define  DW_AT_body_begin 198 
#define  DW_AT_body_end 197 
#define  DW_AT_byte_size 196 
#define  DW_AT_call_column 195 
#define  DW_AT_call_file 194 
#define  DW_AT_call_line 193 
#define  DW_AT_calling_convention 192 
#define  DW_AT_common_reference 191 
#define  DW_AT_comp_dir 190 
#define  DW_AT_const_value 189 
#define  DW_AT_containing_type 188 
#define  DW_AT_count 187 
#define  DW_AT_data_location 186 
#define  DW_AT_data_member_location 185 
#define  DW_AT_decl_column 184 
#define  DW_AT_decl_file 183 
#define  DW_AT_decl_line 182 
#define  DW_AT_declaration 181 
#define  DW_AT_default_value 180 
#define  DW_AT_discr 179 
#define  DW_AT_discr_list 178 
#define  DW_AT_discr_value 177 
#define  DW_AT_element_list 176 
#define  DW_AT_encoding 175 
#define  DW_AT_entry_pc 174 
#define  DW_AT_extension 173 
#define  DW_AT_external 172 
#define  DW_AT_frame_base 171 
#define  DW_AT_friend 170 
#define  DW_AT_high_pc 169 
#define  DW_AT_identifier_case 168 
#define  DW_AT_import 167 
#define  DW_AT_inline 166 
#define  DW_AT_is_optional 165 
#define  DW_AT_language 164 
#define  DW_AT_location 163 
#define  DW_AT_low_pc 162 
#define  DW_AT_lower_bound 161 
#define  DW_AT_mac_info 160 
#define  DW_AT_macro_info 159 
#define  DW_AT_member 158 
#define  DW_AT_name 157 
#define  DW_AT_namelist_items 156 
#define  DW_AT_ordering 155 
#define  DW_AT_priority 154 
#define  DW_AT_producer 153 
#define  DW_AT_prototyped 152 
#define  DW_AT_ranges 151 
#define  DW_AT_return_addr 150 
#define  DW_AT_segment 149 
#define  DW_AT_sf_names 148 
#define  DW_AT_sibling 147 
#define  DW_AT_specification 146 
#define  DW_AT_src_coords 145 
#define  DW_AT_src_info 144 
#define  DW_AT_start_scope 143 
#define  DW_AT_static_link 142 
#define  DW_AT_stmt_list 141 
#define  DW_AT_stride 140 
#define  DW_AT_stride_size 139 
#define  DW_AT_string_length 138 
#define  DW_AT_subscr_data 137 
#define  DW_AT_trampoline 136 
#define  DW_AT_type 135 
#define  DW_AT_upper_bound 134 
#define  DW_AT_use_UTF8 133 
#define  DW_AT_use_location 132 
#define  DW_AT_variable_parameter 131 
#define  DW_AT_virtuality 130 
#define  DW_AT_visibility 129 
#define  DW_AT_vtable_elem_location 128 

__attribute__((used)) static char *
dwarf_attr_name (unsigned attr)
{
  switch (attr)
    {
    case DW_AT_sibling:
      return "DW_AT_sibling";
    case DW_AT_location:
      return "DW_AT_location";
    case DW_AT_name:
      return "DW_AT_name";
    case DW_AT_ordering:
      return "DW_AT_ordering";
    case DW_AT_subscr_data:
      return "DW_AT_subscr_data";
    case DW_AT_byte_size:
      return "DW_AT_byte_size";
    case DW_AT_bit_offset:
      return "DW_AT_bit_offset";
    case DW_AT_bit_size:
      return "DW_AT_bit_size";
    case DW_AT_element_list:
      return "DW_AT_element_list";
    case DW_AT_stmt_list:
      return "DW_AT_stmt_list";
    case DW_AT_low_pc:
      return "DW_AT_low_pc";
    case DW_AT_high_pc:
      return "DW_AT_high_pc";
    case DW_AT_language:
      return "DW_AT_language";
    case DW_AT_member:
      return "DW_AT_member";
    case DW_AT_discr:
      return "DW_AT_discr";
    case DW_AT_discr_value:
      return "DW_AT_discr_value";
    case DW_AT_visibility:
      return "DW_AT_visibility";
    case DW_AT_import:
      return "DW_AT_import";
    case DW_AT_string_length:
      return "DW_AT_string_length";
    case DW_AT_common_reference:
      return "DW_AT_common_reference";
    case DW_AT_comp_dir:
      return "DW_AT_comp_dir";
    case DW_AT_const_value:
      return "DW_AT_const_value";
    case DW_AT_containing_type:
      return "DW_AT_containing_type";
    case DW_AT_default_value:
      return "DW_AT_default_value";
    case DW_AT_inline:
      return "DW_AT_inline";
    case DW_AT_is_optional:
      return "DW_AT_is_optional";
    case DW_AT_lower_bound:
      return "DW_AT_lower_bound";
    case DW_AT_producer:
      return "DW_AT_producer";
    case DW_AT_prototyped:
      return "DW_AT_prototyped";
    case DW_AT_return_addr:
      return "DW_AT_return_addr";
    case DW_AT_start_scope:
      return "DW_AT_start_scope";
    case DW_AT_stride_size:
      return "DW_AT_stride_size";
    case DW_AT_upper_bound:
      return "DW_AT_upper_bound";
    case DW_AT_abstract_origin:
      return "DW_AT_abstract_origin";
    case DW_AT_accessibility:
      return "DW_AT_accessibility";
    case DW_AT_address_class:
      return "DW_AT_address_class";
    case DW_AT_artificial:
      return "DW_AT_artificial";
    case DW_AT_base_types:
      return "DW_AT_base_types";
    case DW_AT_calling_convention:
      return "DW_AT_calling_convention";
    case DW_AT_count:
      return "DW_AT_count";
    case DW_AT_data_member_location:
      return "DW_AT_data_member_location";
    case DW_AT_decl_column:
      return "DW_AT_decl_column";
    case DW_AT_decl_file:
      return "DW_AT_decl_file";
    case DW_AT_decl_line:
      return "DW_AT_decl_line";
    case DW_AT_declaration:
      return "DW_AT_declaration";
    case DW_AT_discr_list:
      return "DW_AT_discr_list";
    case DW_AT_encoding:
      return "DW_AT_encoding";
    case DW_AT_external:
      return "DW_AT_external";
    case DW_AT_frame_base:
      return "DW_AT_frame_base";
    case DW_AT_friend:
      return "DW_AT_friend";
    case DW_AT_identifier_case:
      return "DW_AT_identifier_case";
    case DW_AT_macro_info:
      return "DW_AT_macro_info";
    case DW_AT_namelist_items:
      return "DW_AT_namelist_items";
    case DW_AT_priority:
      return "DW_AT_priority";
    case DW_AT_segment:
      return "DW_AT_segment";
    case DW_AT_specification:
      return "DW_AT_specification";
    case DW_AT_static_link:
      return "DW_AT_static_link";
    case DW_AT_type:
      return "DW_AT_type";
    case DW_AT_use_location:
      return "DW_AT_use_location";
    case DW_AT_variable_parameter:
      return "DW_AT_variable_parameter";
    case DW_AT_virtuality:
      return "DW_AT_virtuality";
    case DW_AT_vtable_elem_location:
      return "DW_AT_vtable_elem_location";
    case DW_AT_allocated:
      return "DW_AT_allocated";
    case DW_AT_associated:
      return "DW_AT_associated";
    case DW_AT_data_location:
      return "DW_AT_data_location";
    case DW_AT_stride:
      return "DW_AT_stride";
    case DW_AT_entry_pc:
      return "DW_AT_entry_pc";
    case DW_AT_use_UTF8:
      return "DW_AT_use_UTF8";
    case DW_AT_extension:
      return "DW_AT_extension";
    case DW_AT_ranges:
      return "DW_AT_ranges";
    case DW_AT_trampoline:
      return "DW_AT_trampoline";
    case DW_AT_call_column:
      return "DW_AT_call_column";
    case DW_AT_call_file:
      return "DW_AT_call_file";
    case DW_AT_call_line:
      return "DW_AT_call_line";
#ifdef MIPS
    case DW_AT_MIPS_fde:
      return "DW_AT_MIPS_fde";
    case DW_AT_MIPS_loop_begin:
      return "DW_AT_MIPS_loop_begin";
    case DW_AT_MIPS_tail_loop_begin:
      return "DW_AT_MIPS_tail_loop_begin";
    case DW_AT_MIPS_epilog_begin:
      return "DW_AT_MIPS_epilog_begin";
    case DW_AT_MIPS_loop_unroll_factor:
      return "DW_AT_MIPS_loop_unroll_factor";
    case DW_AT_MIPS_software_pipeline_depth:
      return "DW_AT_MIPS_software_pipeline_depth";
#endif
    case DW_AT_MIPS_linkage_name:
      return "DW_AT_MIPS_linkage_name";

    case DW_AT_sf_names:
      return "DW_AT_sf_names";
    case DW_AT_src_info:
      return "DW_AT_src_info";
    case DW_AT_mac_info:
      return "DW_AT_mac_info";
    case DW_AT_src_coords:
      return "DW_AT_src_coords";
    case DW_AT_body_begin:
      return "DW_AT_body_begin";
    case DW_AT_body_end:
      return "DW_AT_body_end";
    case DW_AT_GNU_vector:
      return "DW_AT_GNU_vector";
    default:
      return "DW_AT_<unknown>";
    }
}
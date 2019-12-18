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
typedef  enum dwarf_call_frame_info { ____Placeholder_dwarf_call_frame_info } dwarf_call_frame_info ;
typedef  enum dw_cfi_oprnd_type { ____Placeholder_dw_cfi_oprnd_type } dw_cfi_oprnd_type ;

/* Variables and functions */
#define  DW_CFA_GNU_args_size 149 
#define  DW_CFA_GNU_window_save 148 
#define  DW_CFA_MIPS_advance_loc8 147 
#define  DW_CFA_advance_loc1 146 
#define  DW_CFA_advance_loc2 145 
#define  DW_CFA_advance_loc4 144 
#define  DW_CFA_def_cfa 143 
#define  DW_CFA_def_cfa_expression 142 
#define  DW_CFA_def_cfa_offset 141 
#define  DW_CFA_def_cfa_offset_sf 140 
#define  DW_CFA_def_cfa_register 139 
#define  DW_CFA_def_cfa_sf 138 
#define  DW_CFA_expression 137 
#define  DW_CFA_nop 136 
#define  DW_CFA_offset 135 
#define  DW_CFA_offset_extended 134 
#define  DW_CFA_offset_extended_sf 133 
#define  DW_CFA_register 132 
#define  DW_CFA_restore_extended 131 
#define  DW_CFA_same_value 130 
#define  DW_CFA_set_loc 129 
#define  DW_CFA_undefined 128 
 int dw_cfi_oprnd_addr ; 
 int dw_cfi_oprnd_loc ; 
 int dw_cfi_oprnd_offset ; 
 int dw_cfi_oprnd_reg_num ; 
 int dw_cfi_oprnd_unused ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static enum dw_cfi_oprnd_type
dw_cfi_oprnd1_desc (enum dwarf_call_frame_info cfi)
{
  switch (cfi)
    {
    case DW_CFA_nop:
    case DW_CFA_GNU_window_save:
      return dw_cfi_oprnd_unused;

    case DW_CFA_set_loc:
    case DW_CFA_advance_loc1:
    case DW_CFA_advance_loc2:
    case DW_CFA_advance_loc4:
    case DW_CFA_MIPS_advance_loc8:
      return dw_cfi_oprnd_addr;

    case DW_CFA_offset:
    case DW_CFA_offset_extended:
    case DW_CFA_def_cfa:
    case DW_CFA_offset_extended_sf:
    case DW_CFA_def_cfa_sf:
    case DW_CFA_restore_extended:
    case DW_CFA_undefined:
    case DW_CFA_same_value:
    case DW_CFA_def_cfa_register:
    case DW_CFA_register:
      return dw_cfi_oprnd_reg_num;

    case DW_CFA_def_cfa_offset:
    case DW_CFA_GNU_args_size:
    case DW_CFA_def_cfa_offset_sf:
      return dw_cfi_oprnd_offset;

    case DW_CFA_def_cfa_expression:
    case DW_CFA_expression:
      return dw_cfi_oprnd_loc;

    default:
      gcc_unreachable ();
    }
}
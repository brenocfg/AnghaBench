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
#define  DW_CFA_def_cfa 133 
#define  DW_CFA_def_cfa_sf 132 
#define  DW_CFA_offset 131 
#define  DW_CFA_offset_extended 130 
#define  DW_CFA_offset_extended_sf 129 
#define  DW_CFA_register 128 
 int dw_cfi_oprnd_offset ; 
 int dw_cfi_oprnd_reg_num ; 
 int dw_cfi_oprnd_unused ; 

__attribute__((used)) static enum dw_cfi_oprnd_type
dw_cfi_oprnd2_desc (enum dwarf_call_frame_info cfi)
{
  switch (cfi)
    {
    case DW_CFA_def_cfa:
    case DW_CFA_def_cfa_sf:
    case DW_CFA_offset:
    case DW_CFA_offset_extended_sf:
    case DW_CFA_offset_extended:
      return dw_cfi_oprnd_offset;

    case DW_CFA_register:
      return dw_cfi_oprnd_reg_num;

    default:
      return dw_cfi_oprnd_unused;
    }
}
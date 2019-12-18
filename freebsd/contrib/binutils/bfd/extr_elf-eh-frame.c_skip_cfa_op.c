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
typedef  int bfd_vma ;
typedef  int bfd_byte ;
typedef  int bfd_boolean ;

/* Variables and functions */
#define  DW_CFA_GNU_args_size 157 
#define  DW_CFA_GNU_negative_offset_extended 156 
#define  DW_CFA_GNU_window_save 155 
#define  DW_CFA_MIPS_advance_loc8 154 
#define  DW_CFA_advance_loc 153 
#define  DW_CFA_advance_loc1 152 
#define  DW_CFA_advance_loc2 151 
#define  DW_CFA_advance_loc4 150 
#define  DW_CFA_def_cfa 149 
#define  DW_CFA_def_cfa_expression 148 
#define  DW_CFA_def_cfa_offset 147 
#define  DW_CFA_def_cfa_offset_sf 146 
#define  DW_CFA_def_cfa_register 145 
#define  DW_CFA_def_cfa_sf 144 
#define  DW_CFA_expression 143 
#define  DW_CFA_nop 142 
#define  DW_CFA_offset 141 
#define  DW_CFA_offset_extended 140 
#define  DW_CFA_offset_extended_sf 139 
#define  DW_CFA_register 138 
#define  DW_CFA_remember_state 137 
#define  DW_CFA_restore 136 
#define  DW_CFA_restore_extended 135 
#define  DW_CFA_restore_state 134 
#define  DW_CFA_same_value 133 
#define  DW_CFA_set_loc 132 
#define  DW_CFA_undefined 131 
#define  DW_CFA_val_expression 130 
#define  DW_CFA_val_offset 129 
#define  DW_CFA_val_offset_sf 128 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  read_byte (int**,int*,int*) ; 
 int /*<<< orphan*/  read_uleb128 (int**,int*,int*) ; 
 int skip_bytes (int**,int*,int) ; 
 int skip_leb128 (int**,int*) ; 

__attribute__((used)) static bfd_boolean
skip_cfa_op (bfd_byte **iter, bfd_byte *end, unsigned int encoded_ptr_width)
{
  bfd_byte op;
  bfd_vma length;

  if (!read_byte (iter, end, &op))
    return FALSE;

  switch (op & 0xc0 ? op & 0xc0 : op)
    {
    case DW_CFA_nop:
    case DW_CFA_advance_loc:
    case DW_CFA_restore:
    case DW_CFA_remember_state:
    case DW_CFA_restore_state:
    case DW_CFA_GNU_window_save:
      /* No arguments.  */
      return TRUE;

    case DW_CFA_offset:
    case DW_CFA_restore_extended:
    case DW_CFA_undefined:
    case DW_CFA_same_value:
    case DW_CFA_def_cfa_register:
    case DW_CFA_def_cfa_offset:
    case DW_CFA_def_cfa_offset_sf:
    case DW_CFA_GNU_args_size:
      /* One leb128 argument.  */
      return skip_leb128 (iter, end);

    case DW_CFA_val_offset:
    case DW_CFA_val_offset_sf:
    case DW_CFA_offset_extended:
    case DW_CFA_register:
    case DW_CFA_def_cfa:
    case DW_CFA_offset_extended_sf:
    case DW_CFA_GNU_negative_offset_extended:
    case DW_CFA_def_cfa_sf:
      /* Two leb128 arguments.  */
      return (skip_leb128 (iter, end)
	      && skip_leb128 (iter, end));

    case DW_CFA_def_cfa_expression:
      /* A variable-length argument.  */
      return (read_uleb128 (iter, end, &length)
	      && skip_bytes (iter, end, length));

    case DW_CFA_expression:
    case DW_CFA_val_expression:
      /* A leb128 followed by a variable-length argument.  */
      return (skip_leb128 (iter, end)
	      && read_uleb128 (iter, end, &length)
	      && skip_bytes (iter, end, length));

    case DW_CFA_set_loc:
      return skip_bytes (iter, end, encoded_ptr_width);

    case DW_CFA_advance_loc1:
      return skip_bytes (iter, end, 1);

    case DW_CFA_advance_loc2:
      return skip_bytes (iter, end, 2);

    case DW_CFA_advance_loc4:
      return skip_bytes (iter, end, 4);

    case DW_CFA_MIPS_advance_loc8:
      return skip_bytes (iter, end, 8);

    default:
      return FALSE;
    }
}
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
#define  DW_ATE_address 136 
#define  DW_ATE_boolean 135 
#define  DW_ATE_complex_float 134 
#define  DW_ATE_float 133 
#define  DW_ATE_imaginary_float 132 
#define  DW_ATE_signed 131 
#define  DW_ATE_signed_char 130 
#define  DW_ATE_unsigned 129 
#define  DW_ATE_unsigned_char 128 

__attribute__((used)) static char *
dwarf_type_encoding_name (unsigned enc)
{
  switch (enc)
    {
    case DW_ATE_address:
      return "DW_ATE_address";
    case DW_ATE_boolean:
      return "DW_ATE_boolean";
    case DW_ATE_complex_float:
      return "DW_ATE_complex_float";
    case DW_ATE_float:
      return "DW_ATE_float";
    case DW_ATE_signed:
      return "DW_ATE_signed";
    case DW_ATE_signed_char:
      return "DW_ATE_signed_char";
    case DW_ATE_unsigned:
      return "DW_ATE_unsigned";
    case DW_ATE_unsigned_char:
      return "DW_ATE_unsigned_char";
    case DW_ATE_imaginary_float:
      return "DW_ATE_imaginary_float";
    default:
      return "DW_ATE_<unknown>";
    }
}
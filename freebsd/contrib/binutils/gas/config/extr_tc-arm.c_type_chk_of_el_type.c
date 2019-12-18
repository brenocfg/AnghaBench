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
typedef  enum neon_type_mask { ____Placeholder_neon_type_mask } neon_type_mask ;
typedef  enum neon_el_type { ____Placeholder_neon_el_type } neon_el_type ;

/* Variables and functions */
#define  NT_float 133 
#define  NT_integer 132 
#define  NT_poly 131 
#define  NT_signed 130 
#define  NT_unsigned 129 
#define  NT_untyped 128 
 int N_16 ; 
 int N_32 ; 
 int N_64 ; 
 int N_8 ; 
 int N_F32 ; 
 int N_F64 ; 
 int N_I16 ; 
 int N_I32 ; 
 int N_I64 ; 
 int N_I8 ; 
 int N_P16 ; 
 int N_P8 ; 
 int N_S16 ; 
 int N_S32 ; 
 int N_S64 ; 
 int N_S8 ; 
 int N_U16 ; 
 int N_U32 ; 
 int N_U64 ; 
 int N_U8 ; 
 int N_UTYP ; 

__attribute__((used)) static enum neon_type_mask
type_chk_of_el_type (enum neon_el_type type, unsigned size)
{
  switch (type)
    {
    case NT_untyped:
      switch (size)
        {
        case 8:  return N_8;
        case 16: return N_16;
        case 32: return N_32;
        case 64: return N_64;
        default: ;
        }
      break;

    case NT_integer:
      switch (size)
        {
        case 8:  return N_I8;
        case 16: return N_I16;
        case 32: return N_I32;
        case 64: return N_I64;
        default: ;
        }
      break;

    case NT_float:
      switch (size)
        {
        case 32: return N_F32;
        case 64: return N_F64;
        default: ;
        }
      break;

    case NT_poly:
      switch (size)
        {
        case 8:  return N_P8;
        case 16: return N_P16;
        default: ;
        }
      break;

    case NT_signed:
      switch (size)
        {
        case 8:  return N_S8;
        case 16: return N_S16;
        case 32: return N_S32;
        case 64: return N_S64;
        default: ;
        }
      break;

    case NT_unsigned:
      switch (size)
        {
        case 8:  return N_U8;
        case 16: return N_U16;
        case 32: return N_U32;
        case 64: return N_U64;
        default: ;
        }
      break;

    default: ;
    }
  
  return N_UTYP;
}
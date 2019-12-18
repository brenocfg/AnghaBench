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
 int FAIL ; 
 int NT_float ; 
 int NT_integer ; 
 int NT_poly ; 
 int NT_signed ; 
 int NT_unsigned ; 
 int NT_untyped ; 
 int N_16 ; 
 int N_32 ; 
 int N_64 ; 
 int N_8 ; 
 int N_EQK ; 
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
 int SUCCESS ; 

__attribute__((used)) static int
el_type_of_type_chk (enum neon_el_type *type, unsigned *size,
                     enum neon_type_mask mask)
{
  if ((mask & N_EQK) != 0)
    return FAIL;

  if ((mask & (N_S8 | N_U8 | N_I8 | N_8 | N_P8)) != 0)
    *size = 8;
  else if ((mask & (N_S16 | N_U16 | N_I16 | N_16 | N_P16)) != 0)
    *size = 16;
  else if ((mask & (N_S32 | N_U32 | N_I32 | N_32 | N_F32)) != 0)
    *size = 32;
  else if ((mask & (N_S64 | N_U64 | N_I64 | N_64 | N_F64)) != 0)
    *size = 64;
  else
    return FAIL;

  if ((mask & (N_S8 | N_S16 | N_S32 | N_S64)) != 0)
    *type = NT_signed;
  else if ((mask & (N_U8 | N_U16 | N_U32 | N_U64)) != 0)
    *type = NT_unsigned;
  else if ((mask & (N_I8 | N_I16 | N_I32 | N_I64)) != 0)
    *type = NT_integer;
  else if ((mask & (N_8 | N_16 | N_32 | N_64)) != 0)
    *type = NT_untyped;
  else if ((mask & (N_P8 | N_P16)) != 0)
    *type = NT_poly;
  else if ((mask & (N_F32 | N_F64)) != 0)
    *type = NT_float;
  else
    return FAIL;
  
  return SUCCESS;
}
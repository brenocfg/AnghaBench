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
typedef  enum neon_el_type { ____Placeholder_neon_el_type } neon_el_type ;

/* Variables and functions */
 int NT_float ; 
 int NT_integer ; 
 int NT_signed ; 
 int NT_unsigned ; 
 int NT_untyped ; 
 unsigned int N_DBL ; 
 unsigned int N_EQK ; 
 unsigned int N_FLT ; 
 unsigned int N_HLF ; 
 unsigned int N_INT ; 
 unsigned int N_SGN ; 
 unsigned int N_SIZ ; 
 unsigned int N_UNS ; 

__attribute__((used)) static void
neon_modify_type_size (unsigned typebits, enum neon_el_type *g_type,
                       unsigned *g_size)
{
  /* Allow modification to be made to types which are constrained to be
     based on the key element, based on bits set alongside N_EQK.  */
  if ((typebits & N_EQK) != 0)
    {
      if ((typebits & N_HLF) != 0)
	*g_size /= 2;
      else if ((typebits & N_DBL) != 0)
	*g_size *= 2;
      if ((typebits & N_SGN) != 0)
	*g_type = NT_signed;
      else if ((typebits & N_UNS) != 0)
        *g_type = NT_unsigned;
      else if ((typebits & N_INT) != 0)
        *g_type = NT_integer;
      else if ((typebits & N_FLT) != 0)
        *g_type = NT_float;
      else if ((typebits & N_SIZ) != 0)
        *g_type = NT_untyped;
    }
}
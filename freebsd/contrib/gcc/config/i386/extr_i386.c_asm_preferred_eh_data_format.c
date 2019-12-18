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
 scalar_t__ CM_MEDIUM ; 
 scalar_t__ CM_MEDIUM_PIC ; 
 scalar_t__ CM_SMALL ; 
 scalar_t__ CM_SMALL_PIC ; 
 int DW_EH_PE_absptr ; 
 int DW_EH_PE_indirect ; 
 int DW_EH_PE_pcrel ; 
 int DW_EH_PE_sdata4 ; 
 int DW_EH_PE_sdata8 ; 
 int DW_EH_PE_udata4 ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 scalar_t__ flag_pic ; 
 scalar_t__ ix86_cmodel ; 

int
asm_preferred_eh_data_format (int code, int global)
{
  if (flag_pic)
    {
      int type = DW_EH_PE_sdata8;
      if (!TARGET_64BIT
	  || ix86_cmodel == CM_SMALL_PIC
	  || (ix86_cmodel == CM_MEDIUM_PIC && (global || code)))
	type = DW_EH_PE_sdata4;
      return (global ? DW_EH_PE_indirect : 0) | DW_EH_PE_pcrel | type;
    }
  if (ix86_cmodel == CM_SMALL
      || (ix86_cmodel == CM_MEDIUM && code))
    return DW_EH_PE_udata4;
  return DW_EH_PE_absptr;
}
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
 int SHF_MEP_VLIW ; 
 char* _ (char*) ; 

int
mep_elf_section_letter (int letter, char **ptrmsg)
{
  if (letter == 'v')
    return SHF_MEP_VLIW;

  *ptrmsg = _("Bad .section directive: want a,v,w,x,M,S in string");
  return 0;
}
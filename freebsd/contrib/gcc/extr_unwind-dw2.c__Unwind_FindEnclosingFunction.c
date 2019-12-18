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
struct dwarf_fde {int dummy; } ;
struct dwarf_eh_bases {void* func; } ;

/* Variables and functions */
 struct dwarf_fde* _Unwind_Find_FDE (void*,struct dwarf_eh_bases*) ; 

void *
_Unwind_FindEnclosingFunction (void *pc)
{
  struct dwarf_eh_bases bases;
  const struct dwarf_fde *fde = _Unwind_Find_FDE (pc-1, &bases);
  if (fde)
    return bases.func;
  else
    return NULL;
}
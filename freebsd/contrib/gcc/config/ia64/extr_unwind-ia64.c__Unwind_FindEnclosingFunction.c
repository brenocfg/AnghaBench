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
struct unw_table_entry {scalar_t__ start_offset; } ;

/* Variables and functions */
 struct unw_table_entry* _Unwind_FindTableEntry (void*,unsigned long*,unsigned long*) ; 

void *
_Unwind_FindEnclosingFunction (void *pc)
{
  struct unw_table_entry *ent;
  unsigned long segment_base, gp;

  ent = _Unwind_FindTableEntry (pc, &segment_base, &gp);
  if (ent == NULL)
    return NULL;
  else
    return (void *)(segment_base + ent->start_offset);
}
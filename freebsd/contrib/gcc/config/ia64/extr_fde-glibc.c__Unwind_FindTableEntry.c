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
struct unw_table_entry {int dummy; } ;
struct unw_ia64_callback_data {unsigned long* segment_base; unsigned long* gp; struct unw_table_entry* ret; scalar_t__ pc; } ;
typedef  scalar_t__ Elf64_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  _Unwind_IteratePhdrCallback ; 
 scalar_t__ dl_iterate_phdr (int /*<<< orphan*/ ,struct unw_ia64_callback_data*) ; 

struct unw_table_entry *
_Unwind_FindTableEntry (void *pc, unsigned long *segment_base,
                        unsigned long *gp)
{
  struct unw_ia64_callback_data data;

  data.pc = (Elf64_Addr) pc;
  data.segment_base = segment_base;
  data.gp = gp;
  data.ret = NULL;

  if (dl_iterate_phdr (_Unwind_IteratePhdrCallback, &data) < 0)
    return NULL;

  return data.ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct block {int dummy; } ;
typedef  TYPE_2__* alpha_extra_func_info_t ;
struct TYPE_4__ {int framereg; } ;
struct TYPE_5__ {TYPE_1__ pdr; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BLOCK_START (struct block*) ; 
 int /*<<< orphan*/  LABEL_DOMAIN ; 
 int /*<<< orphan*/  MIPS_EFI_SYMBOL_NAME ; 
 scalar_t__ SYMBOL_VALUE (struct symbol*) ; 
 struct block* block_for_pc (scalar_t__) ; 
 int /*<<< orphan*/  find_pc_partial_function (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 struct symbol* lookup_symbol (int /*<<< orphan*/ ,struct block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static alpha_extra_func_info_t
find_proc_desc (CORE_ADDR pc)
{
  struct block *b = block_for_pc (pc);
  alpha_extra_func_info_t proc_desc = NULL;
  struct symbol *sym = NULL;

  if (b)
    {
      CORE_ADDR startaddr;
      find_pc_partial_function (pc, NULL, &startaddr, NULL);

      if (startaddr > BLOCK_START (b))
	/* This is the "pathological" case referred to in a comment in
	   print_frame_info.  It might be better to move this check into
	   symbol reading.  */
	sym = NULL;
      else
	sym = lookup_symbol (MIPS_EFI_SYMBOL_NAME, b, LABEL_DOMAIN, 0, NULL);
    }

  if (sym)
    {
      proc_desc = (alpha_extra_func_info_t) SYMBOL_VALUE (sym);

      /* If we never found a PDR for this function in symbol reading,
	 then examine prologues to find the information.  */
      if (proc_desc->pdr.framereg == -1)
	proc_desc = NULL;
    }

  return proc_desc;
}
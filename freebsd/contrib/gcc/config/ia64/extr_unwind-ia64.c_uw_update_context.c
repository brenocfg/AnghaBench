#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct _Unwind_Context {unsigned long* pfs_loc; unsigned long bsp; scalar_t__ psp; scalar_t__ sp; } ;
struct TYPE_8__ {TYPE_1__* reg; } ;
struct TYPE_9__ {scalar_t__ when_target; int /*<<< orphan*/  no_reg_stack_frame; TYPE_2__ curr; } ;
typedef  TYPE_3__ _Unwind_FrameState ;
struct TYPE_7__ {scalar_t__ when; scalar_t__ where; scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_HANDLE_UNWABI (struct _Unwind_Context*,TYPE_3__*) ; 
 long UNW_NUM_REGS ; 
 long UNW_REG_BSP ; 
 size_t UNW_REG_PRI_UNAT_GR ; 
 size_t UNW_REG_PRI_UNAT_MEM ; 
 size_t UNW_REG_PSP ; 
 scalar_t__ UNW_WHERE_NONE ; 
 scalar_t__ ia64_rse_skip_regs (unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  uw_update_reg_address (struct _Unwind_Context*,TYPE_3__*,long) ; 

__attribute__((used)) static void
uw_update_context (struct _Unwind_Context *context, _Unwind_FrameState *fs)
{
  long i;

#ifdef MD_HANDLE_UNWABI
  MD_HANDLE_UNWABI (context, fs);
#endif

  context->sp = context->psp;

  /* First, set PSP.  Subsequent instructions may depend on this value.  */
  if (fs->when_target > fs->curr.reg[UNW_REG_PSP].when)
    {
      if (fs->curr.reg[UNW_REG_PSP].where == UNW_WHERE_NONE)
	context->psp = context->psp + fs->curr.reg[UNW_REG_PSP].val;
      else
	uw_update_reg_address (context, fs, UNW_REG_PSP);
    }

  /* Determine the location of the primary UNaT.  */
  {
    int i;
    if (fs->when_target < fs->curr.reg[UNW_REG_PRI_UNAT_GR].when)
      i = UNW_REG_PRI_UNAT_MEM;
    else if (fs->when_target < fs->curr.reg[UNW_REG_PRI_UNAT_MEM].when)
      i = UNW_REG_PRI_UNAT_GR;
    else if (fs->curr.reg[UNW_REG_PRI_UNAT_MEM].when
	     > fs->curr.reg[UNW_REG_PRI_UNAT_GR].when)
      i = UNW_REG_PRI_UNAT_MEM;
    else
      i = UNW_REG_PRI_UNAT_GR;
    uw_update_reg_address (context, fs, i);
  }

  /* Compute the addresses of all registers saved in this frame.  */
  for (i = UNW_REG_BSP; i < UNW_NUM_REGS; ++i)
    uw_update_reg_address (context, fs, i);

  /* Unwind BSP for the local registers allocated this frame.  */
  /* ??? What to do with stored BSP or BSPSTORE registers.  */
  /* We assert that we are either at a call site, or we have
     just unwound through a signal frame.  In either case
     pfs_loc is valid.	*/
  if (!(fs -> no_reg_stack_frame))
    {
      unsigned long pfs = *context->pfs_loc;
      unsigned long sol = (pfs >> 7) & 0x7f;
      context->bsp = (unsigned long)
	ia64_rse_skip_regs ((unsigned long *) context->bsp, -sol);
    }
}
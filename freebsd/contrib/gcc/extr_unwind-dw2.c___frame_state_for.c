#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct frame_state {int* saved; int /*<<< orphan*/  eh_ptr; int /*<<< orphan*/  args_size; int /*<<< orphan*/  retaddr_column; int /*<<< orphan*/  cfa_reg; int /*<<< orphan*/  cfa_offset; int /*<<< orphan*/ * reg_or_offset; } ;
struct _Unwind_Context {int /*<<< orphan*/  args_size; void* ra; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_2__* reg; } ;
struct TYPE_9__ {scalar_t__ cfa_how; int /*<<< orphan*/  eh_ptr; int /*<<< orphan*/  retaddr_column; int /*<<< orphan*/  cfa_reg; int /*<<< orphan*/  cfa_offset; TYPE_3__ regs; } ;
typedef  TYPE_4__ _Unwind_FrameState ;
struct TYPE_6__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  reg; } ;
struct TYPE_7__ {int how; TYPE_1__ loc; } ;

/* Variables and functions */
 scalar_t__ CFA_EXP ; 
 int /*<<< orphan*/  EXTENDED_CONTEXT_BIT ; 
 int PRE_GCC3_DWARF_FRAME_REGISTERS ; 
#define  REG_SAVED_OFFSET 129 
#define  REG_SAVED_REG 128 
 scalar_t__ _URC_NO_REASON ; 
 int /*<<< orphan*/  memset (struct _Unwind_Context*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uw_frame_state_for (struct _Unwind_Context*,TYPE_4__*) ; 

struct frame_state *
__frame_state_for (void *pc_target, struct frame_state *state_in)
{
  struct _Unwind_Context context;
  _Unwind_FrameState fs;
  int reg;

  memset (&context, 0, sizeof (struct _Unwind_Context));
  context.flags = EXTENDED_CONTEXT_BIT;
  context.ra = pc_target + 1;

  if (uw_frame_state_for (&context, &fs) != _URC_NO_REASON)
    return 0;

  /* We have no way to pass a location expression for the CFA to our
     caller.  It wouldn't understand it anyway.  */
  if (fs.cfa_how == CFA_EXP)
    return 0;

  for (reg = 0; reg < PRE_GCC3_DWARF_FRAME_REGISTERS + 1; reg++)
    {
      state_in->saved[reg] = fs.regs.reg[reg].how;
      switch (state_in->saved[reg])
	{
	case REG_SAVED_REG:
	  state_in->reg_or_offset[reg] = fs.regs.reg[reg].loc.reg;
	  break;
	case REG_SAVED_OFFSET:
	  state_in->reg_or_offset[reg] = fs.regs.reg[reg].loc.offset;
	  break;
	default:
	  state_in->reg_or_offset[reg] = 0;
	  break;
	}
    }

  state_in->cfa_offset = fs.cfa_offset;
  state_in->cfa_reg = fs.cfa_reg;
  state_in->retaddr_column = fs.retaddr_column;
  state_in->args_size = context.args_size;
  state_in->eh_ptr = fs.eh_ptr;

  return state_in;
}
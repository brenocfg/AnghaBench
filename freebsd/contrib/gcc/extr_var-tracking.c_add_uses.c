#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* rtx ;
struct TYPE_4__ {void* loc; } ;
struct TYPE_5__ {void* insn; TYPE_1__ u; void* type; } ;
typedef  TYPE_2__ micro_operation ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_6__ {int /*<<< orphan*/  n_mos; TYPE_2__* mos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FOR_INSN (void*) ; 
 int /*<<< orphan*/  INT_MEM_OFFSET (void*) ; 
 scalar_t__ MEM_EXPR (void*) ; 
 scalar_t__ MEM_P (void*) ; 
 void* MO_USE ; 
 void* MO_USE_NO_VAR ; 
 scalar_t__ REG_EXPR (void*) ; 
 int /*<<< orphan*/  REG_OFFSET (void*) ; 
 scalar_t__ REG_P (void*) ; 
 TYPE_3__* VTI (int /*<<< orphan*/ ) ; 
 scalar_t__ offset_valid_for_tracked_p (int /*<<< orphan*/ ) ; 
 scalar_t__ track_expr_p (scalar_t__) ; 

__attribute__((used)) static int
add_uses (rtx *loc, void *insn)
{
  if (REG_P (*loc))
    {
      basic_block bb = BLOCK_FOR_INSN ((rtx) insn);
      micro_operation *mo = VTI (bb)->mos + VTI (bb)->n_mos++;

      if (REG_EXPR (*loc)
	  && track_expr_p (REG_EXPR (*loc))
	  && offset_valid_for_tracked_p (REG_OFFSET (*loc)))
	mo->type = MO_USE;
      else
	mo->type = MO_USE_NO_VAR;
      mo->u.loc = *loc;
      mo->insn = (rtx) insn;
    }
  else if (MEM_P (*loc)
	   && MEM_EXPR (*loc)
	   && track_expr_p (MEM_EXPR (*loc))
	   && offset_valid_for_tracked_p (INT_MEM_OFFSET (*loc)))
    {
      basic_block bb = BLOCK_FOR_INSN ((rtx) insn);
      micro_operation *mo = VTI (bb)->mos + VTI (bb)->n_mos++;

      mo->type = MO_USE;
      mo->u.loc = *loc;
      mo->insn = (rtx) insn;
    }

  return 0;
}
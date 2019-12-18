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
struct propagate_block_info {int dummy; } ;
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  regset_head ;
typedef  TYPE_3__* basic_block ;
struct TYPE_8__ {TYPE_1__* rtl; } ;
struct TYPE_9__ {TYPE_2__ il; } ;
struct TYPE_7__ {int /*<<< orphan*/  global_live_at_end; } ;
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 int /*<<< orphan*/  AND_COMPL_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BB_END (TYPE_3__*) ; 
 TYPE_3__* BLOCK_FOR_INSN (scalar_t__) ; 
 int /*<<< orphan*/  CLEAR_REG_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COPY_REG_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_REG_SET (int /*<<< orphan*/ *) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  free_propagate_block_info (struct propagate_block_info*) ; 
 struct propagate_block_info* init_propagate_block_info (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ propagate_one_insn (struct propagate_block_info*,scalar_t__) ; 
 int /*<<< orphan*/  renumbered_reg_set_to_hard_reg_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clear_regs_live_in_seq (HARD_REG_SET * regs, rtx insn, int length)
{
  basic_block bb;
  regset_head live;
  HARD_REG_SET hlive;
  struct propagate_block_info *pbi;
  rtx x;
  int i;

  /* Initialize liveness propagation.  */
  bb = BLOCK_FOR_INSN (insn);
  INIT_REG_SET (&live);
  COPY_REG_SET (&live, bb->il.rtl->global_live_at_end);
  pbi = init_propagate_block_info (bb, &live, NULL, NULL, 0);

  /* Propagate until INSN if found.  */
  for (x = BB_END (bb); x != insn;)
    x = propagate_one_insn (pbi, x);

  /* Clear registers live after INSN.  */
  renumbered_reg_set_to_hard_reg_set (&hlive, &live);
  AND_COMPL_HARD_REG_SET (*regs, hlive);

  /* Clear registers live in and before the sequence.  */
  for (i = 0; i < length;)
    {
      rtx prev = propagate_one_insn (pbi, x);

      if (INSN_P (x))
        {
          renumbered_reg_set_to_hard_reg_set (&hlive, &live);
          AND_COMPL_HARD_REG_SET (*regs, hlive);
          i++;
        }

      x = prev;
    }

  /* Free unused data.  */
  free_propagate_block_info (pbi);
  CLEAR_REG_SET (&live);
}
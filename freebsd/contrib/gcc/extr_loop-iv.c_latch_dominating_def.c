#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct df_reg_info {struct df_ref* reg_chain; } ;
struct df_ref {struct df_ref* next_reg; } ;
struct df_rd_bb_info {int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_3__ {int /*<<< orphan*/  latch; } ;

/* Variables and functions */
 struct df_rd_bb_info* DF_RD_BB_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DF_REF_BB (struct df_ref*) ; 
 int /*<<< orphan*/  DF_REF_ID (struct df_ref*) ; 
 struct df_reg_info* DF_REG_DEF_GET (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_loop ; 
 int /*<<< orphan*/  df ; 
 int /*<<< orphan*/  just_once_each_iteration_p (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
latch_dominating_def (rtx reg, struct df_ref **def)
{
  struct df_ref *single_rd = NULL, *adef;
  unsigned regno = REGNO (reg);
  struct df_reg_info *reg_info = DF_REG_DEF_GET (df, regno);
  struct df_rd_bb_info *bb_info = DF_RD_BB_INFO (df, current_loop->latch);

  for (adef = reg_info->reg_chain; adef; adef = adef->next_reg)
    {
      if (!bitmap_bit_p (bb_info->out, DF_REF_ID (adef)))
	continue;

      /* More than one reaching definition.  */
      if (single_rd)
	return false;

      if (!just_once_each_iteration_p (current_loop, DF_REF_BB (adef)))
	return false;

      single_rd = adef;
    }

  *def = single_rd;
  return true;
}
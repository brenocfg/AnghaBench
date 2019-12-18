#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int n_operands; int n_dups; void*** dup_loc; void*** operand_loc; void** operand; } ;

/* Variables and functions */
 scalar_t__ GET_CODE (void*) ; 
 scalar_t__ MEM_P (void*) ; 
 scalar_t__ MULT ; 
 scalar_t__ PLUS ; 
 scalar_t__ SUBREG ; 
 void* alter_subreg (void**) ; 
 int /*<<< orphan*/  extract_insn_cached (int /*<<< orphan*/ ) ; 
 TYPE_1__ recog_data ; 
 void* walk_alter_subreg (void**) ; 

void
cleanup_subreg_operands (rtx insn)
{
  int i;
  extract_insn_cached (insn);
  for (i = 0; i < recog_data.n_operands; i++)
    {
      /* The following test cannot use recog_data.operand when testing
	 for a SUBREG: the underlying object might have been changed
	 already if we are inside a match_operator expression that
	 matches the else clause.  Instead we test the underlying
	 expression directly.  */
      if (GET_CODE (*recog_data.operand_loc[i]) == SUBREG)
	recog_data.operand[i] = alter_subreg (recog_data.operand_loc[i]);
      else if (GET_CODE (recog_data.operand[i]) == PLUS
	       || GET_CODE (recog_data.operand[i]) == MULT
	       || MEM_P (recog_data.operand[i]))
	recog_data.operand[i] = walk_alter_subreg (recog_data.operand_loc[i]);
    }

  for (i = 0; i < recog_data.n_dups; i++)
    {
      if (GET_CODE (*recog_data.dup_loc[i]) == SUBREG)
	*recog_data.dup_loc[i] = alter_subreg (recog_data.dup_loc[i]);
      else if (GET_CODE (*recog_data.dup_loc[i]) == PLUS
	       || GET_CODE (*recog_data.dup_loc[i]) == MULT
	       || MEM_P (*recog_data.dup_loc[i]))
	*recog_data.dup_loc[i] = walk_alter_subreg (recog_data.dup_loc[i]);
    }
}
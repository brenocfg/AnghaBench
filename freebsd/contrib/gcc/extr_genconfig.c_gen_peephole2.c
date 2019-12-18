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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MATCH_DUP ; 
 scalar_t__ MATCH_SCRATCH ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max_insns_per_peep2 ; 
 int /*<<< orphan*/  walk_insn_part (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_peephole2 (rtx peep)
{
  int i, n;

  /* Look through the patterns that are matched
     to compute the maximum operand number.  */
  for (i = XVECLEN (peep, 0) - 1; i >= 0; --i)
    walk_insn_part (XVECEXP (peep, 0, i), 1, 0);

  /* Look at the number of insns this insn can be matched from.  */
  for (i = XVECLEN (peep, 0) - 1, n = 0; i >= 0; --i)
    if (GET_CODE (XVECEXP (peep, 0, i)) != MATCH_DUP
	&& GET_CODE (XVECEXP (peep, 0, i)) != MATCH_SCRATCH)
      n++;
  if (n > max_insns_per_peep2)
    max_insns_per_peep2 = n;
}
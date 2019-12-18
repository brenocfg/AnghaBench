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
 scalar_t__ XVEC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ clobbers_seen_this_insn ; 
 scalar_t__ max_clobbers_per_insn ; 
 int /*<<< orphan*/  walk_insn_part (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_expand (rtx insn)
{
  int i;

  /* Walk the insn pattern to gather the #define's status.  */

  /* Note that we don't bother recording the number of MATCH_DUPs
     that occur in a gen_expand, because only reload cares about that.  */
  if (XVEC (insn, 1) != 0)
    for (i = 0; i < XVECLEN (insn, 1); i++)
      {
	/* Compute the maximum SETs and CLOBBERS
	   in any one of the sub-insns;
	   don't sum across all of them.  */
	clobbers_seen_this_insn = 0;

	walk_insn_part (XVECEXP (insn, 1, i), 0, 0);

	if (clobbers_seen_this_insn > max_clobbers_per_insn)
	  max_clobbers_per_insn = clobbers_seen_this_insn;
      }
}
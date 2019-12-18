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
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ BARRIER_P (scalar_t__) ; 
 scalar_t__ BB_END (int /*<<< orphan*/ ) ; 
 scalar_t__ next_nonnote_insn (scalar_t__) ; 
 scalar_t__ tablejump_p (scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 

rtx
get_last_bb_insn (basic_block bb)
{
  rtx tmp;
  rtx end = BB_END (bb);

  /* Include any jump table following the basic block.  */
  if (tablejump_p (end, NULL, &tmp))
    end = tmp;

  /* Include any barriers that may follow the basic block.  */
  tmp = next_nonnote_insn (end);
  while (tmp && BARRIER_P (tmp))
    {
      end = tmp;
      tmp = next_nonnote_insn (end);
    }

  return end;
}
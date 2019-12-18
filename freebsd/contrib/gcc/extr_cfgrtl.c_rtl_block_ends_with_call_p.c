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
 scalar_t__ BB_END (int /*<<< orphan*/ ) ; 
 scalar_t__ BB_HEAD (int /*<<< orphan*/ ) ; 
 int CALL_P (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ keep_with_call_p (scalar_t__) ; 

__attribute__((used)) static bool
rtl_block_ends_with_call_p (basic_block bb)
{
  rtx insn = BB_END (bb);

  while (!CALL_P (insn)
	 && insn != BB_HEAD (bb)
	 && keep_with_call_p (insn))
    insn = PREV_INSN (insn);
  return (CALL_P (insn));
}
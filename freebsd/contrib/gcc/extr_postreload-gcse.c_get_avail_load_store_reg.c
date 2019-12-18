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
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 

__attribute__((used)) static rtx
get_avail_load_store_reg (rtx insn)
{
  if (REG_P (SET_DEST (PATTERN (insn))))
    /* A load.  */
    return SET_DEST(PATTERN(insn));
  else
    {
      /* A store.  */
      gcc_assert (REG_P (SET_SRC (PATTERN (insn))));
      return SET_SRC (PATTERN (insn));
    }
}
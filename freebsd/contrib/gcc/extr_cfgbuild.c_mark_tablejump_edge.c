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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 
 int BLOCK_USED_BY_TABLEJUMP ; 
 int FULL_STATE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_STATE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_tablejump_edge (rtx label)
{
  basic_block bb;

  gcc_assert (LABEL_P (label));
  /* See comment in make_label_edge.  */
  if (INSN_UID (label) == 0)
    return;
  bb = BLOCK_FOR_INSN (label);
  SET_STATE (bb, FULL_STATE (bb) | BLOCK_USED_BY_TABLEJUMP);
}
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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** alloca (int) ; 
 int /*<<< orphan*/  emit_group_load_1 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
emit_group_load (rtx dst, rtx src, tree type, int ssize)
{
  rtx *tmps;
  int i;

  tmps = alloca (sizeof (rtx) * XVECLEN (dst, 0));
  emit_group_load_1 (tmps, dst, src, type, ssize);

  /* Copy the extracted pieces into the proper (probable) hard regs.  */
  for (i = 0; i < XVECLEN (dst, 0); i++)
    {
      rtx d = XEXP (XVECEXP (dst, 0, i), 0);
      if (d == NULL)
	continue;
      emit_move_insn (d, tmps[i]);
    }
}
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
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

void
emit_group_move (rtx dst, rtx src)
{
  int i;

  gcc_assert (GET_CODE (src) == PARALLEL
	      && GET_CODE (dst) == PARALLEL
	      && XVECLEN (src, 0) == XVECLEN (dst, 0));

  /* Skip first entry if NULL.  */
  for (i = XEXP (XVECEXP (src, 0, 0), 0) ? 0 : 1; i < XVECLEN (src, 0); i++)
    emit_move_insn (XEXP (XVECEXP (dst, 0, i), 0),
		    XEXP (XVECEXP (src, 0, i), 0));
}
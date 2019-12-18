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
 int /*<<< orphan*/  SYMBOLIC_CONST (int /*<<< orphan*/ ) ; 

int
legitimate_pic_operand_p (rtx op)
{
  /* Accept all non-symbolic constants.  */
  if (!SYMBOLIC_CONST (op))
    return 1;

  /* Reject everything else; must be handled
     via emit_symbolic_move.  */
  return 0;
}
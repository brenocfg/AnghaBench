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
 scalar_t__ TARGET_CPU_ZARCH ; 
 scalar_t__ TLS_SYMBOLIC_CONST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ flag_pic ; 
 scalar_t__ larl_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
legitimate_constant_p (rtx op)
{
  /* Accept all non-symbolic constants.  */
  if (!SYMBOLIC_CONST (op))
    return 1;

  /* Accept immediate LARL operands.  */
  if (TARGET_CPU_ZARCH && larl_operand (op, VOIDmode))
    return 1;

  /* Thread-local symbols are never legal constants.  This is
     so that emit_call knows that computing such addresses
     might require a function call.  */
  if (TLS_SYMBOLIC_CONST (op))
    return 0;

  /* In the PIC case, symbolic constants must *not* be
     forced into the literal pool.  We accept them here,
     so that they will be handled by emit_symbolic_move.  */
  if (flag_pic)
    return 1;

  /* All remaining non-PIC symbolic constants are
     forced into the literal pool.  */
  return 0;
}
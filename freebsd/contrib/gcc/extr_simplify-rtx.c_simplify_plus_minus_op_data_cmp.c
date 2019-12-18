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
struct simplify_plus_minus_op_data {int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int commutative_operand_precedence (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
simplify_plus_minus_op_data_cmp (const void *p1, const void *p2)
{
  const struct simplify_plus_minus_op_data *d1 = p1;
  const struct simplify_plus_minus_op_data *d2 = p2;
  int result;

  result = (commutative_operand_precedence (d2->op)
	    - commutative_operand_precedence (d1->op));
  if (result)
    return result;

  /* Group together equal REGs to do more simplification.  */
  if (REG_P (d1->op) && REG_P (d2->op))
    return REGNO (d1->op) - REGNO (d2->op);
  else
    return 0;
}
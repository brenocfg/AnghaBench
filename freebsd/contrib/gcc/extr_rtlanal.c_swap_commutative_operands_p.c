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
 scalar_t__ commutative_operand_precedence (int /*<<< orphan*/ ) ; 

int
swap_commutative_operands_p (rtx x, rtx y)
{
  return (commutative_operand_precedence (x)
	  < commutative_operand_precedence (y));
}
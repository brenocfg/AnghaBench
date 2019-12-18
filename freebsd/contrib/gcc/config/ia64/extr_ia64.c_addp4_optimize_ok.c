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
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ basereg_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
addp4_optimize_ok (rtx op1, rtx op2)
{
  return (basereg_operand (op1, GET_MODE(op1)) !=
	  basereg_operand (op2, GET_MODE(op2)));
}
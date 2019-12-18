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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TRULY_NOOP_TRUNCATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUNCATE ; 
 int /*<<< orphan*/  gen_lowpart (int,int /*<<< orphan*/ ) ; 
 scalar_t__ reg_truncated_to_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_unary (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
gen_lowpart_or_truncate (enum machine_mode mode, rtx x)
{
  if (GET_MODE_SIZE (GET_MODE (x)) <= GET_MODE_SIZE (mode)
      || TRULY_NOOP_TRUNCATION (GET_MODE_BITSIZE (mode),
				GET_MODE_BITSIZE (GET_MODE (x)))
      || (REG_P (x) && reg_truncated_to_mode (mode, x)))
    return gen_lowpart (mode, x);
  else
    return simplify_gen_unary (TRUNCATE, mode, x, GET_MODE (x));
}
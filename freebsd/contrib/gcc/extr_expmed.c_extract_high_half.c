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
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 int /*<<< orphan*/  SCALAR_FLOAT_MODE_P (int) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_modes (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_shift (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_highpart (int,int /*<<< orphan*/ ) ; 
 int word_mode ; 

__attribute__((used)) static rtx
extract_high_half (enum machine_mode mode, rtx op)
{
  enum machine_mode wider_mode;

  if (mode == word_mode)
    return gen_highpart (mode, op);

  gcc_assert (!SCALAR_FLOAT_MODE_P (mode));

  wider_mode = GET_MODE_WIDER_MODE (mode);
  op = expand_shift (RSHIFT_EXPR, wider_mode, op,
		     build_int_cst (NULL_TREE, GET_MODE_BITSIZE (mode)), 0, 1);
  return convert_modes (mode, wider_mode, op, 0);
}
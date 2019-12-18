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
 scalar_t__ ADDR_DIFF_VEC ; 
 scalar_t__ ADDR_VEC ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ JUMP_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int get_attr_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mips16_insn_length (rtx insn)
{
  if (JUMP_P (insn))
    {
      rtx body = PATTERN (insn);
      if (GET_CODE (body) == ADDR_VEC)
	return GET_MODE_SIZE (GET_MODE (body)) * XVECLEN (body, 0);
      if (GET_CODE (body) == ADDR_DIFF_VEC)
	return GET_MODE_SIZE (GET_MODE (body)) * XVECLEN (body, 1);
    }
  return get_attr_length (insn);
}
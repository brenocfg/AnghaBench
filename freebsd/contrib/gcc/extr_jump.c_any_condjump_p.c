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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ IF_THEN_ELSE ; 
 int LABEL_REF ; 
 int PC ; 
 int RETURN ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pc_set (int /*<<< orphan*/ ) ; 

int
any_condjump_p (rtx insn)
{
  rtx x = pc_set (insn);
  enum rtx_code a, b;

  if (!x)
    return 0;
  if (GET_CODE (SET_SRC (x)) != IF_THEN_ELSE)
    return 0;

  a = GET_CODE (XEXP (SET_SRC (x), 1));
  b = GET_CODE (XEXP (SET_SRC (x), 2));

  return ((b == PC && (a == LABEL_REF || a == RETURN))
	  || (a == PC && (b == LABEL_REF || b == RETURN)));
}
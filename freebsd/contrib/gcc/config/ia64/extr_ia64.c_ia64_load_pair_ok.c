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
 int CONST_INT ; 
 int /*<<< orphan*/  FP_REGNO_P (int /*<<< orphan*/ ) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 int MEM ; 
 scalar_t__ MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
#define  POST_DEC 131 
#define  POST_INC 130 
#define  POST_MODIFY 129 
#define  REG 128 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  abort () ; 

int
ia64_load_pair_ok (rtx dst, rtx src)
{
  if (GET_CODE (dst) != REG || !FP_REGNO_P (REGNO (dst)))
    return 0;
  if (GET_CODE (src) != MEM || MEM_VOLATILE_P (src))
    return 0;
  switch (GET_CODE (XEXP (src, 0)))
    {
    case REG:
    case POST_INC:
      break;
    case POST_DEC:
      return 0;
    case POST_MODIFY:
      {
	rtx adjust = XEXP (XEXP (XEXP (src, 0), 1), 1);

	if (GET_CODE (adjust) != CONST_INT
	    || INTVAL (adjust) != GET_MODE_SIZE (GET_MODE (src)))
	  return 0;
      }
      break;
    default:
      abort ();
    }
  return 1;
}
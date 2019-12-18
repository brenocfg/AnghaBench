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
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  POST_DEC 133 
#define  POST_INC 132 
#define  POST_MODIFY 131 
#define  PRE_DEC 130 
#define  PRE_INC 129 
#define  PRE_MODIFY 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

int
auto_inc_p (rtx x)
{
  switch (GET_CODE (x))
    {
    case PRE_INC:
    case POST_INC:
    case PRE_DEC:
    case POST_DEC:
    case PRE_MODIFY:
    case POST_MODIFY:
      /* There are no REG_INC notes for SP.  */
      if (XEXP (x, 0) != stack_pointer_rtx)
	return 1;
    default:
      break;
    }
  return 0;
}
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
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mips_split_const (rtx x, rtx *base, HOST_WIDE_INT *offset)
{
  *offset = 0;

  if (GET_CODE (x) == CONST)
    {
      x = XEXP (x, 0);
      if (GET_CODE (x) == PLUS && GET_CODE (XEXP (x, 1)) == CONST_INT)
	{
	  *offset += INTVAL (XEXP (x, 1));
	  x = XEXP (x, 0);
	}
    }
  *base = x;
}
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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS ; 
 scalar_t__ REG ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_MINIMAL_TOC ; 
 scalar_t__ TARGET_TOC ; 
 scalar_t__ TOC_REGISTER ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ constant_pool_expr_p (int /*<<< orphan*/ ) ; 

bool
legitimate_constant_pool_address_p (rtx x)
{
  return (TARGET_TOC
	  && GET_CODE (x) == PLUS
	  && GET_CODE (XEXP (x, 0)) == REG
	  && (TARGET_MINIMAL_TOC || REGNO (XEXP (x, 0)) == TOC_REGISTER)
	  && constant_pool_expr_p (XEXP (x, 1)));
}
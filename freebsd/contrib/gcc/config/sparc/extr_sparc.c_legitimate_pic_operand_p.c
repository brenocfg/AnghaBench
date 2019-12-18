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
 scalar_t__ CONST ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS ; 
 scalar_t__ SPARC_SYMBOL_REF_TLS_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pic_address_needs_scratch (int /*<<< orphan*/ ) ; 

bool
legitimate_pic_operand_p (rtx x)
{
  if (pic_address_needs_scratch (x))
    return false;
  if (SPARC_SYMBOL_REF_TLS_P (x)
      || (GET_CODE (x) == CONST
	  && GET_CODE (XEXP (x, 0)) == PLUS
	  && SPARC_SYMBOL_REF_TLS_P (XEXP (XEXP (x, 0), 0))))
    return false;
  return true;
}
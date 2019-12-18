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
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ PLUS ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ UNSPEC ; 
 scalar_t__ UNSPEC_GOTPCREL ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ix86_delegitimize_address (int /*<<< orphan*/ ) ; 

rtx
ix86_find_base_term (rtx x)
{
  rtx term;

  if (TARGET_64BIT)
    {
      if (GET_CODE (x) != CONST)
	return x;
      term = XEXP (x, 0);
      if (GET_CODE (term) == PLUS
	  && (GET_CODE (XEXP (term, 1)) == CONST_INT
	      || GET_CODE (XEXP (term, 1)) == CONST_DOUBLE))
	term = XEXP (term, 0);
      if (GET_CODE (term) != UNSPEC
	  || XINT (term, 1) != UNSPEC_GOTPCREL)
	return x;

      term = XVECEXP (term, 0, 0);

      if (GET_CODE (term) != SYMBOL_REF
	  && GET_CODE (term) != LABEL_REF)
	return x;

      return term;
    }

  term = ix86_delegitimize_address (x);

  if (GET_CODE (term) != SYMBOL_REF
      && GET_CODE (term) != LABEL_REF)
    return x;

  return term;
}
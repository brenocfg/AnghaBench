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
typedef  int /*<<< orphan*/ * rtx ;
typedef  int RTX_CODE ;

/* Variables and functions */
#define  ATTR_FLAG 134 
 int /*<<< orphan*/  ATTR_IND_SIMPLIFIED_P (int /*<<< orphan*/ *) ; 
#define  EQ_ATTR 133 
#define  EQ_ATTR_ALT 132 
 int GET_CODE (int /*<<< orphan*/ *) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  MATCH_DUP 131 
#define  MATCH_OPERAND 130 
#define  PC 129 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XVEC (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * XVECEXP (int /*<<< orphan*/ *,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ *,int) ; 
 int address_used ; 
 int /*<<< orphan*/  alternative_name ; 
 int /*<<< orphan*/  length_str ; 
 int length_used ; 
 int must_constrain ; 
 int must_extract ; 
 int /*<<< orphan*/  strcmp_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
walk_attr_value (rtx exp)
{
  int i, j;
  const char *fmt;
  RTX_CODE code;

  if (exp == NULL)
    return;

  code = GET_CODE (exp);
  switch (code)
    {
    case SYMBOL_REF:
      if (! ATTR_IND_SIMPLIFIED_P (exp))
	/* Since this is an arbitrary expression, it can look at anything.
	   However, constant expressions do not depend on any particular
	   insn.  */
	must_extract = must_constrain = 1;
      return;

    case MATCH_OPERAND:
      must_extract = 1;
      return;

    case EQ_ATTR_ALT:
      must_extract = must_constrain = 1;
      break;

    case EQ_ATTR:
      if (XSTR (exp, 0) == alternative_name)
	must_extract = must_constrain = 1;
      else if (strcmp_check (XSTR (exp, 0), length_str) == 0)
	length_used = 1;
      return;

    case MATCH_DUP:
      must_extract = 1;
      address_used = 1;
      return;

    case PC:
      address_used = 1;
      return;

    case ATTR_FLAG:
      return;

    default:
      break;
    }

  for (i = 0, fmt = GET_RTX_FORMAT (code); i < GET_RTX_LENGTH (code); i++)
    switch (*fmt++)
      {
      case 'e':
      case 'u':
	walk_attr_value (XEXP (exp, i));
	break;

      case 'E':
	if (XVEC (exp, i) != NULL)
	  for (j = 0; j < XVECLEN (exp, i); j++)
	    walk_attr_value (XVECEXP (exp, i, j));
	break;
      }
}
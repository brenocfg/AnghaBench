#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct data {TYPE_1__* operand; int /*<<< orphan*/  lineno; } ;
typedef  scalar_t__ rtx ;
struct TYPE_2__ {int seen; int strict_low; char* predicate; int address_p; int eliminable; void* constraint; void* mode; int /*<<< orphan*/  n_alternatives; } ;

/* Variables and functions */
#define  ADDRESS 136 
 int GET_CODE (scalar_t__) ; 
 void* GET_MODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  MATCH_DUP 135 
#define  MATCH_OPERAND 134 
#define  MATCH_OPERATOR 133 
#define  MATCH_OP_DUP 132 
#define  MATCH_PARALLEL 131 
#define  MATCH_PAR_DUP 130 
#define  MATCH_SCRATCH 129 
 int MAX_MAX_OPERANDS ; 
#define  STRICT_LOW_PART 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int XINT (scalar_t__,int /*<<< orphan*/ ) ; 
 void* XSTR (scalar_t__,int) ; 
 int /*<<< orphan*/ * XVEC (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int have_error ; 
 int max_opno ; 
 int /*<<< orphan*/  message_with_line (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  n_occurrences (char,void*) ; 
 int /*<<< orphan*/  num_dups ; 
 void* strip_whitespace (void*) ; 

__attribute__((used)) static void
scan_operands (struct data *d, rtx part, int this_address_p,
	       int this_strict_low)
{
  int i, j;
  const char *format_ptr;
  int opno;

  if (part == 0)
    return;

  switch (GET_CODE (part))
    {
    case MATCH_OPERAND:
      opno = XINT (part, 0);
      if (opno > max_opno)
	max_opno = opno;
      if (max_opno >= MAX_MAX_OPERANDS)
	{
	  message_with_line (d->lineno,
			     "maximum number of operands exceeded");
	  have_error = 1;
	  return;
	}
      if (d->operand[opno].seen)
	{
	  message_with_line (d->lineno,
			     "repeated operand number %d\n", opno);
	  have_error = 1;
	}

      d->operand[opno].seen = 1;
      d->operand[opno].mode = GET_MODE (part);
      d->operand[opno].strict_low = this_strict_low;
      d->operand[opno].predicate = XSTR (part, 1);
      d->operand[opno].constraint = strip_whitespace (XSTR (part, 2));
      d->operand[opno].n_alternatives
	= n_occurrences (',', d->operand[opno].constraint) + 1;
      d->operand[opno].address_p = this_address_p;
      d->operand[opno].eliminable = 1;
      return;

    case MATCH_SCRATCH:
      opno = XINT (part, 0);
      if (opno > max_opno)
	max_opno = opno;
      if (max_opno >= MAX_MAX_OPERANDS)
	{
	  message_with_line (d->lineno,
			     "maximum number of operands exceeded");
	  have_error = 1;
	  return;
	}
      if (d->operand[opno].seen)
	{
	  message_with_line (d->lineno,
			     "repeated operand number %d\n", opno);
	  have_error = 1;
	}

      d->operand[opno].seen = 1;
      d->operand[opno].mode = GET_MODE (part);
      d->operand[opno].strict_low = 0;
      d->operand[opno].predicate = "scratch_operand";
      d->operand[opno].constraint = strip_whitespace (XSTR (part, 1));
      d->operand[opno].n_alternatives
	= n_occurrences (',', d->operand[opno].constraint) + 1;
      d->operand[opno].address_p = 0;
      d->operand[opno].eliminable = 0;
      return;

    case MATCH_OPERATOR:
    case MATCH_PARALLEL:
      opno = XINT (part, 0);
      if (opno > max_opno)
	max_opno = opno;
      if (max_opno >= MAX_MAX_OPERANDS)
	{
	  message_with_line (d->lineno,
			     "maximum number of operands exceeded");
	  have_error = 1;
	  return;
	}
      if (d->operand[opno].seen)
	{
	  message_with_line (d->lineno,
			     "repeated operand number %d\n", opno);
	  have_error = 1;
	}

      d->operand[opno].seen = 1;
      d->operand[opno].mode = GET_MODE (part);
      d->operand[opno].strict_low = 0;
      d->operand[opno].predicate = XSTR (part, 1);
      d->operand[opno].constraint = 0;
      d->operand[opno].address_p = 0;
      d->operand[opno].eliminable = 0;
      for (i = 0; i < XVECLEN (part, 2); i++)
	scan_operands (d, XVECEXP (part, 2, i), 0, 0);
      return;

    case MATCH_DUP:
    case MATCH_OP_DUP:
    case MATCH_PAR_DUP:
      ++num_dups;
      break;

    case ADDRESS:
      scan_operands (d, XEXP (part, 0), 1, 0);
      return;

    case STRICT_LOW_PART:
      scan_operands (d, XEXP (part, 0), 0, 1);
      return;

    default:
      break;
    }

  format_ptr = GET_RTX_FORMAT (GET_CODE (part));

  for (i = 0; i < GET_RTX_LENGTH (GET_CODE (part)); i++)
    switch (*format_ptr++)
      {
      case 'e':
      case 'u':
	scan_operands (d, XEXP (part, i), 0, 0);
	break;
      case 'E':
	if (XVEC (part, i) != NULL)
	  for (j = 0; j < XVECLEN (part, i); j++)
	    scan_operands (d, XVECEXP (part, i, j), 0, 0);
	break;
      }
}
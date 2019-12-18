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
struct table_elt {scalar_t__ related_value; scalar_t__ exp; struct table_elt* next_same_value; struct table_elt* first_same_value; } ;
typedef  scalar_t__ rtx ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  SAFE_HASH (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ get_integer_term (scalar_t__) ; 
 scalar_t__ get_related_value (scalar_t__) ; 
 struct table_elt* lookup (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ plus_constant (scalar_t__,scalar_t__) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static rtx
use_related_value (rtx x, struct table_elt *elt)
{
  struct table_elt *relt = 0;
  struct table_elt *p, *q;
  HOST_WIDE_INT offset;

  /* First, is there anything related known?
     If we have a table element, we can tell from that.
     Otherwise, must look it up.  */

  if (elt != 0 && elt->related_value != 0)
    relt = elt;
  else if (elt == 0 && GET_CODE (x) == CONST)
    {
      rtx subexp = get_related_value (x);
      if (subexp != 0)
	relt = lookup (subexp,
		       SAFE_HASH (subexp, GET_MODE (subexp)),
		       GET_MODE (subexp));
    }

  if (relt == 0)
    return 0;

  /* Search all related table entries for one that has an
     equivalent register.  */

  p = relt;
  while (1)
    {
      /* This loop is strange in that it is executed in two different cases.
	 The first is when X is already in the table.  Then it is searching
	 the RELATED_VALUE list of X's class (RELT).  The second case is when
	 X is not in the table.  Then RELT points to a class for the related
	 value.

	 Ensure that, whatever case we are in, that we ignore classes that have
	 the same value as X.  */

      if (rtx_equal_p (x, p->exp))
	q = 0;
      else
	for (q = p->first_same_value; q; q = q->next_same_value)
	  if (REG_P (q->exp))
	    break;

      if (q)
	break;

      p = p->related_value;

      /* We went all the way around, so there is nothing to be found.
	 Alternatively, perhaps RELT was in the table for some other reason
	 and it has no related values recorded.  */
      if (p == relt || p == 0)
	break;
    }

  if (q == 0)
    return 0;

  offset = (get_integer_term (x) - get_integer_term (p->exp));
  /* Note: OFFSET may be 0 if P->xexp and X are related by commutativity.  */
  return plus_constant (q->exp, offset);
}
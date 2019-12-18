#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mode; TYPE_1__* data; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ mode; size_t code; scalar_t__ veclen; TYPE_2__ pred; int /*<<< orphan*/  intval; int /*<<< orphan*/  num_insns; } ;
struct decision_test {int type; TYPE_3__ u; } ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
struct TYPE_4__ {scalar_t__* codes; } ;

/* Variables and functions */
#define  DT_code 135 
#define  DT_elt_one_int 134 
#define  DT_elt_zero_int 133 
#define  DT_elt_zero_wide 132 
#define  DT_elt_zero_wide_safe 131 
#define  DT_mode 130 
#define  DT_num_insns 129 
 int DT_pred ; 
#define  DT_veclen 128 
 int const DT_veclen_ge ; 
 int NUM_RTX_CODE ; 
 scalar_t__ VOIDmode ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
maybe_both_true_2 (struct decision_test *d1, struct decision_test *d2)
{
  if (d1->type == d2->type)
    {
      switch (d1->type)
	{
	case DT_num_insns:
	  if (d1->u.num_insns == d2->u.num_insns)
	    return 1;
	  else
	    return -1;

	case DT_mode:
	  return d1->u.mode == d2->u.mode;

	case DT_code:
	  return d1->u.code == d2->u.code;

	case DT_veclen:
	  return d1->u.veclen == d2->u.veclen;

	case DT_elt_zero_int:
	case DT_elt_one_int:
	case DT_elt_zero_wide:
	case DT_elt_zero_wide_safe:
	  return d1->u.intval == d2->u.intval;

	default:
	  break;
	}
    }

  /* If either has a predicate that we know something about, set
     things up so that D1 is the one that always has a known
     predicate.  Then see if they have any codes in common.  */

  if (d1->type == DT_pred || d2->type == DT_pred)
    {
      if (d2->type == DT_pred)
	{
	  struct decision_test *tmp;
	  tmp = d1, d1 = d2, d2 = tmp;
	}

      /* If D2 tests a mode, see if it matches D1.  */
      if (d1->u.pred.mode != VOIDmode)
	{
	  if (d2->type == DT_mode)
	    {
	      if (d1->u.pred.mode != d2->u.mode
		  /* The mode of an address_operand predicate is the
		     mode of the memory, not the operand.  It can only
		     be used for testing the predicate, so we must
		     ignore it here.  */
		  && strcmp (d1->u.pred.name, "address_operand") != 0)
		return 0;
	    }
	  /* Don't check two predicate modes here, because if both predicates
	     accept CONST_INT, then both can still be true even if the modes
	     are different.  If they don't accept CONST_INT, there will be a
	     separate DT_mode that will make maybe_both_true_1 return 0.  */
	}

      if (d1->u.pred.data)
	{
	  /* If D2 tests a code, see if it is in the list of valid
	     codes for D1's predicate.  */
	  if (d2->type == DT_code)
	    {
	      if (!d1->u.pred.data->codes[d2->u.code])
		return 0;
	    }

	  /* Otherwise see if the predicates have any codes in common.  */
	  else if (d2->type == DT_pred && d2->u.pred.data)
	    {
	      bool common = false;
	      enum rtx_code c;

	      for (c = 0; c < NUM_RTX_CODE; c++)
		if (d1->u.pred.data->codes[c] && d2->u.pred.data->codes[c])
		  {
		    common = true;
		    break;
		  }

	      if (!common)
		return 0;
	    }
	}
    }

  /* Tests vs veclen may be known when strict equality is involved.  */
  if (d1->type == DT_veclen && d2->type == DT_veclen_ge)
    return d1->u.veclen >= d2->u.veclen;
  if (d1->type == DT_veclen_ge && d2->type == DT_veclen)
    return d2->u.veclen >= d1->u.veclen;

  return -1;
}
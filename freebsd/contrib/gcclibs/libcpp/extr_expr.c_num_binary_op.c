#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
struct TYPE_20__ {int /*<<< orphan*/  skip_eval; } ;
struct TYPE_21__ {TYPE_1__ state; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_22__ {int unsignedp; size_t low; int overflow; scalar_t__ high; } ;
typedef  TYPE_3__ cpp_num ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_PEDWARN ; 
#define  CPP_LSHIFT 131 
#define  CPP_MINUS 130 
 size_t CPP_OPTION (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPP_PEDANTIC (TYPE_2__*) ; 
#define  CPP_PLUS 129 
#define  CPP_RSHIFT 128 
 int /*<<< orphan*/  c99 ; 
 int /*<<< orphan*/  cpp_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ num_lshift (TYPE_3__,size_t,size_t) ; 
 TYPE_3__ num_negate (TYPE_3__,size_t) ; 
 int num_positive (TYPE_3__,size_t) ; 
 TYPE_3__ num_rshift (TYPE_3__,size_t,size_t) ; 
 TYPE_3__ num_trim (TYPE_3__,size_t) ; 
 size_t precision ; 

__attribute__((used)) static cpp_num
num_binary_op (cpp_reader *pfile, cpp_num lhs, cpp_num rhs, enum cpp_ttype op)
{
  cpp_num result;
  size_t precision = CPP_OPTION (pfile, precision);
  size_t n;

  switch (op)
    {
      /* Shifts.  */
    case CPP_LSHIFT:
    case CPP_RSHIFT:
      if (!rhs.unsignedp && !num_positive (rhs, precision))
	{
	  /* A negative shift is a positive shift the other way.  */
	  if (op == CPP_LSHIFT)
	    op = CPP_RSHIFT;
	  else
	    op = CPP_LSHIFT;
	  rhs = num_negate (rhs, precision);
	}
      if (rhs.high)
	n = ~0;			/* Maximal.  */
      else
	n = rhs.low;
      if (op == CPP_LSHIFT)
	lhs = num_lshift (lhs, precision, n);
      else
	lhs = num_rshift (lhs, precision, n);
      break;

      /* Arithmetic.  */
    case CPP_MINUS:
      rhs = num_negate (rhs, precision);
    case CPP_PLUS:
      result.low = lhs.low + rhs.low;
      result.high = lhs.high + rhs.high;
      if (result.low < lhs.low)
	result.high++;
      result.unsignedp = lhs.unsignedp || rhs.unsignedp;
      result.overflow = false;

      result = num_trim (result, precision);
      if (!result.unsignedp)
	{
	  bool lhsp = num_positive (lhs, precision);
	  result.overflow = (lhsp == num_positive (rhs, precision)
			     && lhsp != num_positive (result, precision));
	}
      return result;

      /* Comma.  */
    default: /* case CPP_COMMA: */
      if (CPP_PEDANTIC (pfile) && (!CPP_OPTION (pfile, c99)
				   || !pfile->state.skip_eval))
	cpp_error (pfile, CPP_DL_PEDWARN,
		   "comma operator in operand of #if");
      lhs = rhs;
      break;
    }

  return lhs;
}
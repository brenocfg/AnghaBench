#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ valueT ;
typedef  int /*<<< orphan*/  symbolS ;
typedef  scalar_t__ segT ;
typedef  int operatorT ;
typedef  scalar_t__ offsetT ;
typedef  int /*<<< orphan*/  fragS ;
struct TYPE_3__ {scalar_t__ X_add_number; int X_op; int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/ * X_op_symbol; } ;
typedef  TYPE_1__ expressionS ;
typedef  scalar_t__ bfd_vma ;

/* Variables and functions */
 scalar_t__ OCTETS_PER_BYTE ; 
#define  O_add 153 
#define  O_bit_and 152 
#define  O_bit_exclusive_or 151 
#define  O_bit_inclusive_or 150 
#define  O_bit_not 149 
#define  O_bit_or_not 148 
#define  O_constant 147 
#define  O_divide 146 
#define  O_eq 145 
#define  O_ge 144 
#define  O_gt 143 
#define  O_le 142 
#define  O_left_shift 141 
#define  O_logical_and 140 
#define  O_logical_not 139 
#define  O_logical_or 138 
#define  O_lt 137 
#define  O_modulus 136 
#define  O_multiply 135 
#define  O_ne 134 
#define  O_register 133 
#define  O_right_shift 132 
#define  O_subtract 131 
#define  O_symbol 130 
#define  O_symbol_rva 129 
#define  O_uminus 128 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ absolute_section ; 
 int /*<<< orphan*/  finalize_syms ; 
 int /*<<< orphan*/  frag_offset_fixed_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ reg_section ; 
 int /*<<< orphan*/  snapshot_symbol (int /*<<< orphan*/ **,scalar_t__*,scalar_t__*,int /*<<< orphan*/ **) ; 
 scalar_t__ undefined_section ; 

int
resolve_expression (expressionS *expressionP)
{
  /* Help out with CSE.  */
  valueT final_val = expressionP->X_add_number;
  symbolS *add_symbol = expressionP->X_add_symbol;
  symbolS *op_symbol = expressionP->X_op_symbol;
  operatorT op = expressionP->X_op;
  valueT left, right;
  segT seg_left, seg_right;
  fragS *frag_left, *frag_right;
  bfd_vma frag_off;

  switch (op)
    {
    default:
      return 0;

    case O_constant:
    case O_register:
      left = 0;
      break;

    case O_symbol:
    case O_symbol_rva:
      if (!snapshot_symbol (&add_symbol, &left, &seg_left, &frag_left))
	return 0;

      break;

    case O_uminus:
    case O_bit_not:
    case O_logical_not:
      if (!snapshot_symbol (&add_symbol, &left, &seg_left, &frag_left))
	return 0;

      if (seg_left != absolute_section)
	return 0;

      if (op == O_logical_not)
	left = !left;
      else if (op == O_uminus)
	left = -left;
      else
	left = ~left;
      op = O_constant;
      break;

    case O_multiply:
    case O_divide:
    case O_modulus:
    case O_left_shift:
    case O_right_shift:
    case O_bit_inclusive_or:
    case O_bit_or_not:
    case O_bit_exclusive_or:
    case O_bit_and:
    case O_add:
    case O_subtract:
    case O_eq:
    case O_ne:
    case O_lt:
    case O_le:
    case O_ge:
    case O_gt:
    case O_logical_and:
    case O_logical_or:
      if (!snapshot_symbol (&add_symbol, &left, &seg_left, &frag_left)
	  || !snapshot_symbol (&op_symbol, &right, &seg_right, &frag_right))
	return 0;

      /* Simplify addition or subtraction of a constant by folding the
	 constant into X_add_number.  */
      if (op == O_add)
	{
	  if (seg_right == absolute_section)
	    {
	      final_val += right;
	      op = O_symbol;
	      break;
	    }
	  else if (seg_left == absolute_section)
	    {
	      final_val += left;
	      left = right;
	      seg_left = seg_right;
	      add_symbol = op_symbol;
	      op = O_symbol;
	      break;
	    }
	}
      else if (op == O_subtract)
	{
	  if (seg_right == absolute_section)
	    {
	      final_val -= right;
	      op = O_symbol;
	      break;
	    }
	}

      /* Equality and non-equality tests are permitted on anything.
	 Subtraction, and other comparison operators are permitted if
	 both operands are in the same section.
	 Shifts by constant zero are permitted on anything.
	 Multiplies, bit-ors, and bit-ands with constant zero are
	 permitted on anything.
	 Multiplies and divides by constant one are permitted on
	 anything.
	 Binary operations with both operands being the same register
	 or undefined symbol are permitted if the result doesn't depend
	 on the input value.
	 Otherwise, both operands must be absolute.  We already handled
	 the case of addition or subtraction of a constant above.  */
      frag_off = 0;
      if (!(seg_left == absolute_section
	       && seg_right == absolute_section)
	  && !(op == O_eq || op == O_ne)
	  && !((op == O_subtract
		|| op == O_lt || op == O_le || op == O_ge || op == O_gt)
	       && seg_left == seg_right
	       && (finalize_syms
		   || frag_offset_fixed_p (frag_left, frag_right, &frag_off))
	       && (seg_left != reg_section || left == right)
	       && (seg_left != undefined_section || add_symbol == op_symbol)))
	{
	  if ((seg_left == absolute_section && left == 0)
	      || (seg_right == absolute_section && right == 0))
	    {
	      if (op == O_bit_exclusive_or || op == O_bit_inclusive_or)
		{
		  if (seg_right != absolute_section || right != 0)
		    {
		      seg_left = seg_right;
		      left = right;
		      add_symbol = op_symbol;
		    }
		  op = O_symbol;
		  break;
		}
	      else if (op == O_left_shift || op == O_right_shift)
		{
		  if (seg_left != absolute_section || left != 0)
		    {
		      op = O_symbol;
		      break;
		    }
		}
	      else if (op != O_multiply
		       && op != O_bit_or_not && op != O_bit_and)
	        return 0;
	    }
	  else if (op == O_multiply
		   && seg_left == absolute_section && left == 1)
	    {
	      seg_left = seg_right;
	      left = right;
	      add_symbol = op_symbol;
	      op = O_symbol;
	      break;
	    }
	  else if ((op == O_multiply || op == O_divide)
		   && seg_right == absolute_section && right == 1)
	    {
	      op = O_symbol;
	      break;
	    }
	  else if (left != right
		   || ((seg_left != reg_section || seg_right != reg_section)
		       && (seg_left != undefined_section
			   || seg_right != undefined_section
			   || add_symbol != op_symbol)))
	    return 0;
	  else if (op == O_bit_and || op == O_bit_inclusive_or)
	    {
	      op = O_symbol;
	      break;
	    }
	  else if (op != O_bit_exclusive_or && op != O_bit_or_not)
	    return 0;
	}

      right += frag_off / OCTETS_PER_BYTE;
      switch (op)
	{
	case O_add:			left += right; break;
	case O_subtract:		left -= right; break;
	case O_multiply:		left *= right; break;
	case O_divide:
	  if (right == 0)
	    return 0;
	  left = (offsetT) left / (offsetT) right;
	  break;
	case O_modulus:
	  if (right == 0)
	    return 0;
	  left = (offsetT) left % (offsetT) right;
	  break;
	case O_left_shift:		left <<= right; break;
	case O_right_shift:		left >>= right; break;
	case O_bit_inclusive_or:	left |= right; break;
	case O_bit_or_not:		left |= ~right; break;
	case O_bit_exclusive_or:	left ^= right; break;
	case O_bit_and:			left &= right; break;
	case O_eq:
	case O_ne:
	  left = (left == right
		  && seg_left == seg_right
		  && (finalize_syms || frag_left == frag_right)
		  && (seg_left != undefined_section
		      || add_symbol == op_symbol)
		  ? ~ (valueT) 0 : 0);
	  if (op == O_ne)
	    left = ~left;
	  break;
	case O_lt:
	  left = (offsetT) left <  (offsetT) right ? ~ (valueT) 0 : 0;
	  break;
	case O_le:
	  left = (offsetT) left <= (offsetT) right ? ~ (valueT) 0 : 0;
	  break;
	case O_ge:
	  left = (offsetT) left >= (offsetT) right ? ~ (valueT) 0 : 0;
	  break;
	case O_gt:
	  left = (offsetT) left >  (offsetT) right ? ~ (valueT) 0 : 0;
	  break;
	case O_logical_and:	left = left && right; break;
	case O_logical_or:	left = left || right; break;
	default:		abort ();
	}

      op = O_constant;
      break;
    }

  if (op == O_symbol)
    {
      if (seg_left == absolute_section)
	op = O_constant;
      else if (seg_left == reg_section && final_val == 0)
	op = O_register;
      else if (add_symbol != expressionP->X_add_symbol)
	final_val += left;
      expressionP->X_add_symbol = add_symbol;
    }
  expressionP->X_op = op;

  if (op == O_constant || op == O_register)
    final_val += left;
  expressionP->X_add_number = final_val;

  return 1;
}
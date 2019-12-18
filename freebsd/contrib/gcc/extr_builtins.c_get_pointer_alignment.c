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
typedef  int /*<<< orphan*/  tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  ADDR_EXPR 132 
 unsigned int BITS_PER_UNIT ; 
 int /*<<< orphan*/  CONSTANT_ALIGNMENT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  CONSTANT_CLASS_P (int /*<<< orphan*/ ) ; 
#define  CONVERT_EXPR 131 
 unsigned int DECL_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_P (int /*<<< orphan*/ ) ; 
 int const INDIRECT_REF ; 
 int MIN (unsigned int,unsigned int) ; 
 int const MULT_EXPR ; 
#define  NON_LVALUE_EXPR 130 
#define  NOP_EXPR 129 
#define  PLUS_EXPR 128 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 unsigned int TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int const VIEW_CONVERT_EXPR ; 
 scalar_t__ flag_tree_ter ; 
 int /*<<< orphan*/  get_inner_reference (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 int /*<<< orphan*/  handled_component_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_integerp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ optimize ; 
 unsigned int tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
get_pointer_alignment (tree exp, unsigned int max_align)
{
  unsigned int align, inner;

  /* We rely on TER to compute accurate alignment information.  */
  if (!(optimize && flag_tree_ter))
    return 0;

  if (!POINTER_TYPE_P (TREE_TYPE (exp)))
    return 0;

  align = TYPE_ALIGN (TREE_TYPE (TREE_TYPE (exp)));
  align = MIN (align, max_align);

  while (1)
    {
      switch (TREE_CODE (exp))
	{
	case NOP_EXPR:
	case CONVERT_EXPR:
	case NON_LVALUE_EXPR:
	  exp = TREE_OPERAND (exp, 0);
	  if (! POINTER_TYPE_P (TREE_TYPE (exp)))
	    return align;

	  inner = TYPE_ALIGN (TREE_TYPE (TREE_TYPE (exp)));
	  align = MIN (inner, max_align);
	  break;

	case PLUS_EXPR:
	  /* If sum of pointer + int, restrict our maximum alignment to that
	     imposed by the integer.  If not, we can't do any better than
	     ALIGN.  */
	  if (! host_integerp (TREE_OPERAND (exp, 1), 1))
	    return align;

	  while (((tree_low_cst (TREE_OPERAND (exp, 1), 1))
		  & (max_align / BITS_PER_UNIT - 1))
		 != 0)
	    max_align >>= 1;

	  exp = TREE_OPERAND (exp, 0);
	  break;

	case ADDR_EXPR:
	  /* See what we are pointing at and look at its alignment.  */
	  exp = TREE_OPERAND (exp, 0);
	  inner = max_align;
	  if (handled_component_p (exp))
	    {
	      HOST_WIDE_INT bitsize, bitpos;
	      tree offset;
	      enum machine_mode mode; 
	      int unsignedp, volatilep;

	      exp = get_inner_reference (exp, &bitsize, &bitpos, &offset,
					 &mode, &unsignedp, &volatilep, true);
	      if (bitpos)
		inner = MIN (inner, (unsigned) (bitpos & -bitpos));
	      if (offset && TREE_CODE (offset) == PLUS_EXPR
		  && host_integerp (TREE_OPERAND (offset, 1), 1))
	        {
		  /* Any overflow in calculating offset_bits won't change
		     the alignment.  */
		  unsigned offset_bits
		    = ((unsigned) tree_low_cst (TREE_OPERAND (offset, 1), 1)
		       * BITS_PER_UNIT);

		  if (offset_bits)
		    inner = MIN (inner, (offset_bits & -offset_bits));
		  offset = TREE_OPERAND (offset, 0);
		}
	      if (offset && TREE_CODE (offset) == MULT_EXPR
		  && host_integerp (TREE_OPERAND (offset, 1), 1))
	        {
		  /* Any overflow in calculating offset_factor won't change
		     the alignment.  */
		  unsigned offset_factor
		    = ((unsigned) tree_low_cst (TREE_OPERAND (offset, 1), 1)
		       * BITS_PER_UNIT);

		  if (offset_factor)
		    inner = MIN (inner, (offset_factor & -offset_factor));
		}
	      else if (offset)
		inner = MIN (inner, BITS_PER_UNIT);
	    }
	  if (DECL_P (exp))
	    align = MIN (inner, DECL_ALIGN (exp));
#ifdef CONSTANT_ALIGNMENT
	  else if (CONSTANT_CLASS_P (exp))
	    align = MIN (inner, (unsigned)CONSTANT_ALIGNMENT (exp, align));
#endif
	  else if (TREE_CODE (exp) == VIEW_CONVERT_EXPR
		   || TREE_CODE (exp) == INDIRECT_REF)
	    align = MIN (TYPE_ALIGN (TREE_TYPE (exp)), inner);
	  else
	    align = MIN (align, inner);
	  return MIN (align, max_align);

	default:
	  return align;
	}
    }
}
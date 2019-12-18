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
typedef  scalar_t__ tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  double_int ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  ARRAY_RANGE_REF 134 
#define  ARRAY_REF 133 
 int /*<<< orphan*/  BIGGEST_ALIGNMENT ; 
 int /*<<< orphan*/  BITS_PER_UNIT ; 
#define  BIT_FIELD_REF 132 
 int BIT_FIELD_REF_UNSIGNED (scalar_t__) ; 
 int BLKmode ; 
#define  COMPONENT_REF 131 
 int /*<<< orphan*/  DECL_BIT_FIELD (scalar_t__) ; 
 scalar_t__ DECL_FIELD_BIT_OFFSET (scalar_t__) ; 
 int DECL_MODE (scalar_t__) ; 
 scalar_t__ DECL_SIZE (scalar_t__) ; 
 int DECL_UNSIGNED (scalar_t__) ; 
 int GET_MODE_BITSIZE (int) ; 
#define  IMAGPART_EXPR 130 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
#define  REALPART_EXPR 129 
 int /*<<< orphan*/  STRICT_ALIGNMENT ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_THIS_VOLATILE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ALIGN_OK (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_SIZE (int /*<<< orphan*/ ) ; 
 int TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
#define  VIEW_CONVERT_EXPR 128 
 int VOIDmode ; 
 scalar_t__ array_ref_element_size (scalar_t__) ; 
 scalar_t__ array_ref_low_bound (scalar_t__) ; 
 scalar_t__ bitsize_int (int) ; 
 scalar_t__ bitsize_zero_node ; 
 scalar_t__ component_ref_field_offset (scalar_t__) ; 
 int /*<<< orphan*/  double_int_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ double_int_fits_in_shwi_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int double_int_to_shwi (int /*<<< orphan*/ ) ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ host_integerp (scalar_t__,int) ; 
 int /*<<< orphan*/  integer_zerop (scalar_t__) ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ size_zero_node ; 
 int /*<<< orphan*/  sizetype ; 
 int tree_low_cst (scalar_t__,int) ; 
 int /*<<< orphan*/  tree_to_double_int (scalar_t__) ; 
 int /*<<< orphan*/  uhwi_to_double_int (int /*<<< orphan*/ ) ; 

tree
get_inner_reference (tree exp, HOST_WIDE_INT *pbitsize,
		     HOST_WIDE_INT *pbitpos, tree *poffset,
		     enum machine_mode *pmode, int *punsignedp,
		     int *pvolatilep, bool keep_aligning)
{
  tree size_tree = 0;
  enum machine_mode mode = VOIDmode;
  tree offset = size_zero_node;
  tree bit_offset = bitsize_zero_node;

  /* First get the mode, signedness, and size.  We do this from just the
     outermost expression.  */
  if (TREE_CODE (exp) == COMPONENT_REF)
    {
      size_tree = DECL_SIZE (TREE_OPERAND (exp, 1));
      if (! DECL_BIT_FIELD (TREE_OPERAND (exp, 1)))
	mode = DECL_MODE (TREE_OPERAND (exp, 1));

      *punsignedp = DECL_UNSIGNED (TREE_OPERAND (exp, 1));
    }
  else if (TREE_CODE (exp) == BIT_FIELD_REF)
    {
      size_tree = TREE_OPERAND (exp, 1);
      *punsignedp = BIT_FIELD_REF_UNSIGNED (exp);
    }
  else
    {
      mode = TYPE_MODE (TREE_TYPE (exp));
      *punsignedp = TYPE_UNSIGNED (TREE_TYPE (exp));

      if (mode == BLKmode)
	size_tree = TYPE_SIZE (TREE_TYPE (exp));
      else
	*pbitsize = GET_MODE_BITSIZE (mode);
    }

  if (size_tree != 0)
    {
      if (! host_integerp (size_tree, 1))
	mode = BLKmode, *pbitsize = -1;
      else
	*pbitsize = tree_low_cst (size_tree, 1);
    }

  *pmode = mode;

  /* Compute cumulative bit-offset for nested component-refs and array-refs,
     and find the ultimate containing object.  */
  while (1)
    {
      switch (TREE_CODE (exp))
	{
	case BIT_FIELD_REF:
	  bit_offset = size_binop (PLUS_EXPR, bit_offset,
				   TREE_OPERAND (exp, 2));
	  break;

	case COMPONENT_REF:
	  {
	    tree field = TREE_OPERAND (exp, 1);
	    tree this_offset = component_ref_field_offset (exp);

	    /* If this field hasn't been filled in yet, don't go past it.
	       This should only happen when folding expressions made during
	       type construction.  */
	    if (this_offset == 0)
	      break;

	    offset = size_binop (PLUS_EXPR, offset, this_offset);
	    bit_offset = size_binop (PLUS_EXPR, bit_offset,
				     DECL_FIELD_BIT_OFFSET (field));

	    /* ??? Right now we don't do anything with DECL_OFFSET_ALIGN.  */
	  }
	  break;

	case ARRAY_REF:
	case ARRAY_RANGE_REF:
	  {
	    tree index = TREE_OPERAND (exp, 1);
	    tree low_bound = array_ref_low_bound (exp);
	    tree unit_size = array_ref_element_size (exp);

	    /* We assume all arrays have sizes that are a multiple of a byte.
	       First subtract the lower bound, if any, in the type of the
	       index, then convert to sizetype and multiply by the size of
	       the array element.  */
	    if (! integer_zerop (low_bound))
	      index = fold_build2 (MINUS_EXPR, TREE_TYPE (index),
				   index, low_bound);

	    offset = size_binop (PLUS_EXPR, offset,
			         size_binop (MULT_EXPR,
					     fold_convert (sizetype, index),
					     unit_size));
	  }
	  break;

	case REALPART_EXPR:
	  break;

	case IMAGPART_EXPR:
	  bit_offset = size_binop (PLUS_EXPR, bit_offset,
				   bitsize_int (*pbitsize));
	  break;

	case VIEW_CONVERT_EXPR:
	  if (keep_aligning && STRICT_ALIGNMENT
	      && (TYPE_ALIGN (TREE_TYPE (exp))
	       > TYPE_ALIGN (TREE_TYPE (TREE_OPERAND (exp, 0))))
	      && (TYPE_ALIGN (TREE_TYPE (TREE_OPERAND (exp, 0)))
		  < BIGGEST_ALIGNMENT)
	      && (TYPE_ALIGN_OK (TREE_TYPE (exp))
		  || TYPE_ALIGN_OK (TREE_TYPE (TREE_OPERAND (exp, 0)))))
	    goto done;
	  break;

	default:
	  goto done;
	}

      /* If any reference in the chain is volatile, the effect is volatile.  */
      if (TREE_THIS_VOLATILE (exp))
	*pvolatilep = 1;

      exp = TREE_OPERAND (exp, 0);
    }
 done:

  /* If OFFSET is constant, see if we can return the whole thing as a
     constant bit position.  Make sure to handle overflow during
     this conversion.  */
  if (host_integerp (offset, 0))
    {
      double_int tem = double_int_mul (tree_to_double_int (offset),
				       uhwi_to_double_int (BITS_PER_UNIT));
      tem = double_int_add (tem, tree_to_double_int (bit_offset));
      if (double_int_fits_in_shwi_p (tem))
	{
	  *pbitpos = double_int_to_shwi (tem);
	  *poffset = NULL_TREE;
	  return exp;
	}
    }

  /* Otherwise, split it up.  */
  *pbitpos = tree_low_cst (bit_offset, 0);
  *poffset = offset;

  return exp;
}
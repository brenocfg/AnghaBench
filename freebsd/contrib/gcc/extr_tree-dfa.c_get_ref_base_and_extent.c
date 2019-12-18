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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  ARRAY_RANGE_REF 134 
#define  ARRAY_REF 133 
#define  BIT_FIELD_REF 132 
 int BLKmode ; 
#define  COMPONENT_REF 131 
 scalar_t__ DECL_FIELD_BIT_OFFSET (scalar_t__) ; 
 scalar_t__ DECL_SIZE (scalar_t__) ; 
 int GET_MODE_BITSIZE (int) ; 
#define  IMAGPART_EXPR 130 
 int INTEGER_CST ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
#define  REALPART_EXPR 129 
 int /*<<< orphan*/  SSA_VAR_P (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 int TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_SIZE (int /*<<< orphan*/ ) ; 
#define  VIEW_CONVERT_EXPR 128 
 scalar_t__ array_ref_element_size (scalar_t__) ; 
 scalar_t__ array_ref_low_bound (scalar_t__) ; 
 scalar_t__ bitsize_int (int) ; 
 scalar_t__ bitsize_unit_node ; 
 scalar_t__ bitsize_zero_node ; 
 int /*<<< orphan*/  bitsizetype ; 
 scalar_t__ component_ref_field_offset (scalar_t__) ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ host_integerp (scalar_t__,int) ; 
 int /*<<< orphan*/  integer_zerop (scalar_t__) ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sizetype ; 

tree
get_ref_base_and_extent (tree exp, HOST_WIDE_INT *poffset,
			 HOST_WIDE_INT *psize,
			 HOST_WIDE_INT *pmax_size)
{
  HOST_WIDE_INT bitsize = -1;
  HOST_WIDE_INT maxsize = -1;
  tree size_tree = NULL_TREE;
  tree bit_offset = bitsize_zero_node;
  bool seen_variable_array_ref = false;

  gcc_assert (!SSA_VAR_P (exp));

  /* First get the final access size from just the outermost expression.  */
  if (TREE_CODE (exp) == COMPONENT_REF)
    size_tree = DECL_SIZE (TREE_OPERAND (exp, 1));
  else if (TREE_CODE (exp) == BIT_FIELD_REF)
    size_tree = TREE_OPERAND (exp, 1);
  else
    {
      enum machine_mode mode = TYPE_MODE (TREE_TYPE (exp));
      if (mode == BLKmode)
	size_tree = TYPE_SIZE (TREE_TYPE (exp));
      else
	bitsize = GET_MODE_BITSIZE (mode);
    }
  if (size_tree != NULL_TREE)
    {
      if (! host_integerp (size_tree, 1))
	bitsize = -1;
      else
	bitsize = TREE_INT_CST_LOW (size_tree);
    }

  /* Initially, maxsize is the same as the accessed element size.
     In the following it will only grow (or become -1).  */
  maxsize = bitsize;

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

	    if (this_offset && TREE_CODE (this_offset) == INTEGER_CST)
	      {
		this_offset = size_binop (MULT_EXPR,
					  fold_convert (bitsizetype,
							this_offset),
					  bitsize_unit_node);
		bit_offset = size_binop (PLUS_EXPR,
				         bit_offset, this_offset);
		bit_offset = size_binop (PLUS_EXPR, bit_offset,
					 DECL_FIELD_BIT_OFFSET (field));
	      }
	    else
	      {
		tree csize = TYPE_SIZE (TREE_TYPE (TREE_OPERAND (exp, 0)));
		/* We need to adjust maxsize to the whole structure bitsize.
		   But we can subtract any constant offset seen sofar,
		   because that would get us out of the structure otherwise.  */
		if (maxsize != -1
		    && csize && host_integerp (csize, 1))
		  {
		    maxsize = (TREE_INT_CST_LOW (csize)
			       - TREE_INT_CST_LOW (bit_offset));
		  }
		else
		  maxsize = -1;
	      }
	  }
	  break;

	case ARRAY_REF:
	case ARRAY_RANGE_REF:
	  {
	    tree index = TREE_OPERAND (exp, 1);
	    tree low_bound = array_ref_low_bound (exp);
	    tree unit_size = array_ref_element_size (exp);

	    if (! integer_zerop (low_bound))
	      index = fold_build2 (MINUS_EXPR, TREE_TYPE (index),
				   index, low_bound);
	    index = size_binop (MULT_EXPR,
				fold_convert (sizetype, index), unit_size);
	    if (TREE_CODE (index) == INTEGER_CST)
	      {
		index = size_binop (MULT_EXPR,
				    fold_convert (bitsizetype, index),
				    bitsize_unit_node);
		bit_offset = size_binop (PLUS_EXPR, bit_offset, index);

		/* An array ref with a constant index up in the structure
		   hierarchy will constrain the size of any variable array ref
		   lower in the access hierarchy.  */
		seen_variable_array_ref = false;
	      }
	    else
	      {
		tree asize = TYPE_SIZE (TREE_TYPE (TREE_OPERAND (exp, 0)));
		/* We need to adjust maxsize to the whole array bitsize.
		   But we can subtract any constant offset seen sofar,
		   because that would get us outside of the array otherwise.  */
		if (maxsize != -1
		    && asize && host_integerp (asize, 1))
		  {
		    maxsize = (TREE_INT_CST_LOW (asize)
			       - TREE_INT_CST_LOW (bit_offset));
		  }
		else
		  maxsize = -1;

		/* Remember that we have seen an array ref with a variable
		   index.  */
		seen_variable_array_ref = true;
	      }
	  }
	  break;

	case REALPART_EXPR:
	  break;

	case IMAGPART_EXPR:
	  bit_offset = size_binop (PLUS_EXPR, bit_offset,
				   bitsize_int (bitsize));
	  break;

	case VIEW_CONVERT_EXPR:
	  /* ???  We probably should give up here and bail out.  */
	  break;

	default:
	  goto done;
	}

      exp = TREE_OPERAND (exp, 0);
    }
 done:

  /* We need to deal with variable arrays ending structures such as
       struct { int length; int a[1]; } x;           x.a[d]
       struct { struct { int a; int b; } a[1]; } x;  x.a[d].a
       struct { struct { int a[1]; } a[1]; } x;      x.a[0][d], x.a[d][0]
     where we do not know maxsize for variable index accesses to
     the array.  The simplest way to conservatively deal with this
     is to punt in the case that offset + maxsize reaches the
     base type boundary.  */
  if (seen_variable_array_ref
      && maxsize != -1
      && host_integerp (TYPE_SIZE (TREE_TYPE (exp)), 1)
      && TREE_INT_CST_LOW (bit_offset) + maxsize
	 == TREE_INT_CST_LOW (TYPE_SIZE (TREE_TYPE (exp))))
    maxsize = -1;

  /* ???  Due to negative offsets in ARRAY_REF we can end up with
     negative bit_offset here.  We might want to store a zero offset
     in this case.  */
  *poffset = TREE_INT_CST_LOW (bit_offset);
  *psize = bitsize;
  *pmax_size = maxsize;

  return exp;
}
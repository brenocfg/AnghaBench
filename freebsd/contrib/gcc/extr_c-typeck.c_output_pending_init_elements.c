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
struct init_node {scalar_t__ purpose; struct init_node* parent; struct init_node* right; struct init_node* left; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 
 scalar_t__ bit_position (scalar_t__) ; 
 struct init_node* constructor_pending_elts ; 
 scalar_t__ constructor_type ; 
 scalar_t__ constructor_unfilled_fields ; 
 scalar_t__ constructor_unfilled_index ; 
 int /*<<< orphan*/  output_init_element (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_int_cst_equal (scalar_t__,scalar_t__) ; 
 scalar_t__ tree_int_cst_lt (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
output_pending_init_elements (int all)
{
  struct init_node *elt = constructor_pending_elts;
  tree next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = 0;
  while (elt)
    {
      if (TREE_CODE (constructor_type) == ARRAY_TYPE)
	{
	  if (tree_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (elt->value, true,
				 TREE_TYPE (constructor_type),
				 constructor_unfilled_index, 0);
	  else if (tree_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      if (elt->left)
		elt = elt->left;
	      else
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  break;
		}
	    }
	  else
	    {
	      /* Advance to the next bigger node.  */
	      if (elt->right)
		elt = elt->right;
	      else
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  while (elt->parent && elt->parent->right == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  if (elt && tree_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      break;
		    }
		}
	    }
	}
      else if (TREE_CODE (constructor_type) == RECORD_TYPE
	       || TREE_CODE (constructor_type) == UNION_TYPE)
	{
	  tree ctor_unfilled_bitpos, elt_bitpos;

	  /* If the current record is complete we are done.  */
	  if (constructor_unfilled_fields == 0)
	    break;

	  ctor_unfilled_bitpos = bit_position (constructor_unfilled_fields);
	  elt_bitpos = bit_position (elt->purpose);
	  /* We can't compare fields here because there might be empty
	     fields in between.  */
	  if (tree_int_cst_equal (elt_bitpos, ctor_unfilled_bitpos))
	    {
	      constructor_unfilled_fields = elt->purpose;
	      output_init_element (elt->value, true, TREE_TYPE (elt->purpose),
				   elt->purpose, 0);
	    }
	  else if (tree_int_cst_lt (ctor_unfilled_bitpos, elt_bitpos))
	    {
	      /* Advance to the next smaller node.  */
	      if (elt->left)
		elt = elt->left;
	      else
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  break;
		}
	    }
	  else
	    {
	      /* Advance to the next bigger node.  */
	      if (elt->right)
		elt = elt->right;
	      else
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  while (elt->parent && elt->parent->right == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  if (elt
		      && (tree_int_cst_lt (ctor_unfilled_bitpos,
					   bit_position (elt->purpose))))
		    {
		      next = elt->purpose;
		      break;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  if (!(all && next != 0))
    return;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  if (TREE_CODE (constructor_type) == RECORD_TYPE
      || TREE_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = next;
  else if (TREE_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  goto retry;
}
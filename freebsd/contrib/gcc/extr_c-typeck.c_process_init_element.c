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
typedef  scalar_t__ tree ;
struct constructor_range_stack {scalar_t__ index; scalar_t__ fields; scalar_t__ range_start; scalar_t__ range_end; TYPE_1__* stack; struct constructor_range_stack* next; struct constructor_range_stack* prev; } ;
struct c_expr {scalar_t__ value; scalar_t__ original_code; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {scalar_t__ implicit; struct c_expr replacement_value; } ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ COMPOUND_LITERAL_EXPR ; 
 scalar_t__ DECL_C_BIT_FIELD (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ DECL_SIZE (scalar_t__) ; 
 scalar_t__ INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  OPT_Wtraditional ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ RECORD_TYPE ; 
 int /*<<< orphan*/  RESTORE_SPELLING_DEPTH (int /*<<< orphan*/ ) ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ TYPE_SIZE (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 
 scalar_t__ VECTOR_TYPE ; 
 scalar_t__ bit_position (scalar_t__) ; 
 scalar_t__ bitsize_one_node ; 
 scalar_t__ constructor_bit_index ; 
 int /*<<< orphan*/  constructor_depth ; 
 int /*<<< orphan*/  constructor_designated ; 
 scalar_t__ constructor_fields ; 
 scalar_t__ constructor_index ; 
 scalar_t__ constructor_max_index ; 
 struct constructor_range_stack* constructor_range_stack ; 
 TYPE_1__* constructor_stack ; 
 scalar_t__ constructor_type ; 
 scalar_t__ constructor_unfilled_fields ; 
 scalar_t__ constructor_unfilled_index ; 
 scalar_t__ designator_depth ; 
 scalar_t__ designator_erroneous ; 
 int /*<<< orphan*/  error_init (char*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ flag_isoc99 ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  in_system_header ; 
 scalar_t__ integer_all_onesp (scalar_t__) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 int /*<<< orphan*/  output_init_element (scalar_t__,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  pedwarn_init (char*) ; 
 struct c_expr pop_init_level (int) ; 
 int /*<<< orphan*/  push_array_bounds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_init_level (int) ; 
 int /*<<< orphan*/  push_member_name (scalar_t__) ; 
 scalar_t__ real_zerop (scalar_t__) ; 
 int /*<<< orphan*/  require_constant_value ; 
 scalar_t__ save_expr (scalar_t__) ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ tree_int_cst_equal (scalar_t__,scalar_t__) ; 
 scalar_t__ tree_int_cst_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tree_low_cst (scalar_t__,int) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
process_init_element (struct c_expr value)
{
  tree orig_value = value.value;
  int string_flag = orig_value != 0 && TREE_CODE (orig_value) == STRING_CST;
  bool strict_string = value.original_code == STRING_CST;

  designator_depth = 0;
  designator_erroneous = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  if (string_flag
      && constructor_type
      && TREE_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (TREE_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      if (constructor_stack->replacement_value.value)
	error_init ("excess elements in char array initializer");
      constructor_stack->replacement_value = value;
      return;
    }

  if (constructor_stack->replacement_value.value != 0)
    {
      error_init ("excess elements in struct initializer");
      return;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed.  */
  if (constructor_type == 0)
    return;

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  while (constructor_stack->implicit)
    {
      if ((TREE_CODE (constructor_type) == RECORD_TYPE
	   || TREE_CODE (constructor_type) == UNION_TYPE)
	  && constructor_fields == 0)
	process_init_element (pop_init_level (1));
      else if (TREE_CODE (constructor_type) == ARRAY_TYPE
	       && (constructor_max_index == 0
		   || tree_int_cst_lt (constructor_max_index,
				       constructor_index)))
	process_init_element (pop_init_level (1));
      else
	break;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  if (constructor_range_stack)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      if (TREE_CODE (value.value) != COMPOUND_LITERAL_EXPR
	  || !require_constant_value
	  || flag_isoc99)
	value.value = save_expr (value.value);
    }

  while (1)
    {
      if (TREE_CODE (constructor_type) == RECORD_TYPE)
	{
	  tree fieldtype;
	  enum tree_code fieldcode;

	  if (constructor_fields == 0)
	    {
	      pedwarn_init ("excess elements in struct initializer");
	      break;
	    }

	  fieldtype = TREE_TYPE (constructor_fields);
	  if (fieldtype != error_mark_node)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = TREE_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  if (fieldcode == ARRAY_TYPE
	      && !require_constant_value
	      && TYPE_SIZE (fieldtype) == NULL_TREE
	      && TREE_CHAIN (constructor_fields) == NULL_TREE)
	    {
	      error_init ("non-static initialization of a flexible array member");
	      break;
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  if (value.value != 0
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (TREE_TYPE (fieldtype))
	      && string_flag)
	    value.value = orig_value;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  else if (value.value != 0
		   && value.value != error_mark_node
		   && TYPE_MAIN_VARIANT (TREE_TYPE (value.value)) != fieldtype
		   && (fieldcode == RECORD_TYPE || fieldcode == ARRAY_TYPE
		       || fieldcode == UNION_TYPE))
	    {
	      push_init_level (1);
	      continue;
	    }

	  if (value.value)
	    {
	      push_member_name (constructor_fields);
	      output_init_element (value.value, strict_string,
				   fieldtype, constructor_fields, 1);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  else
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      if (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop (PLUS_EXPR,
				bit_position (constructor_fields),
				DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      if (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = TREE_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  while (constructor_unfilled_fields != 0
			 && DECL_C_BIT_FIELD (constructor_unfilled_fields)
			 && DECL_NAME (constructor_unfilled_fields) == 0)
		    constructor_unfilled_fields =
		      TREE_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = TREE_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  while (constructor_fields != 0
		 && DECL_C_BIT_FIELD (constructor_fields)
		 && DECL_NAME (constructor_fields) == 0)
	    constructor_fields = TREE_CHAIN (constructor_fields);
	}
      else if (TREE_CODE (constructor_type) == UNION_TYPE)
	{
	  tree fieldtype;
	  enum tree_code fieldcode;

	  if (constructor_fields == 0)
	    {
	      pedwarn_init ("excess elements in union initializer");
	      break;
	    }

	  fieldtype = TREE_TYPE (constructor_fields);
	  if (fieldtype != error_mark_node)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = TREE_CODE (fieldtype);

	  /* Warn that traditional C rejects initialization of unions.
	     We skip the warning if the value is zero.  This is done
	     under the assumption that the zero initializer in user
	     code appears conditioned on e.g. __STDC__ to avoid
	     "missing initializer" warnings and relies on default
	     initialization to zero in the traditional C case.
	     We also skip the warning if the initializer is designated,
	     again on the assumption that this must be conditional on
	     __STDC__ anyway (and we've already complained about the
	     member-designator already).  */
	  if (!in_system_header && !constructor_designated
	      && !(value.value && (integer_zerop (value.value)
				   || real_zerop (value.value))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Accept a string constant to initialize a subarray.  */
	  if (value.value != 0
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (TREE_TYPE (fieldtype))
	      && string_flag)
	    value.value = orig_value;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  else if (value.value != 0
		   && value.value != error_mark_node
		   && TYPE_MAIN_VARIANT (TREE_TYPE (value.value)) != fieldtype
		   && (fieldcode == RECORD_TYPE || fieldcode == ARRAY_TYPE
		       || fieldcode == UNION_TYPE))
	    {
	      push_init_level (1);
	      continue;
	    }

	  if (value.value)
	    {
	      push_member_name (constructor_fields);
	      output_init_element (value.value, strict_string,
				   fieldtype, constructor_fields, 1);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  else
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_index = DECL_SIZE (constructor_fields);
	      constructor_unfilled_fields = TREE_CHAIN (constructor_fields);
	    }

	  constructor_fields = 0;
	}
      else if (TREE_CODE (constructor_type) == ARRAY_TYPE)
	{
	  tree elttype = TYPE_MAIN_VARIANT (TREE_TYPE (constructor_type));
	  enum tree_code eltcode = TREE_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  if (value.value != 0
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (TREE_TYPE (elttype))
	      && string_flag)
	    value.value = orig_value;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  else if (value.value != 0
		   && value.value != error_mark_node
		   && TYPE_MAIN_VARIANT (TREE_TYPE (value.value)) != elttype
		   && (eltcode == RECORD_TYPE || eltcode == ARRAY_TYPE
		       || eltcode == UNION_TYPE))
	    {
	      push_init_level (1);
	      continue;
	    }

	  if (constructor_max_index != 0
	      && (tree_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index)))
	    {
	      pedwarn_init ("excess elements in array initializer");
	      break;
	    }

	  /* Now output the actual element.  */
	  if (value.value)
	    {
	      push_array_bounds (tree_low_cst (constructor_index, 1));
	      output_init_element (value.value, strict_string,
				   elttype, constructor_index, 1);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }

	  constructor_index
	    = size_binop (PLUS_EXPR, constructor_index, bitsize_one_node);

	  if (!value.value)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}
      else if (TREE_CODE (constructor_type) == VECTOR_TYPE)
	{
	  tree elttype = TYPE_MAIN_VARIANT (TREE_TYPE (constructor_type));

	 /* Do a basic check of initializer size.  Note that vectors
	    always have a fixed size derived from their type.  */
	  if (tree_int_cst_lt (constructor_max_index, constructor_index))
	    {
	      pedwarn_init ("excess elements in vector initializer");
	      break;
	    }

	  /* Now output the actual element.  */
	  if (value.value)
	    output_init_element (value.value, strict_string,
				 elttype, constructor_index, 1);

	  constructor_index
	    = size_binop (PLUS_EXPR, constructor_index, bitsize_one_node);

	  if (!value.value)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      else if (constructor_type != error_mark_node
	       && constructor_fields == 0)
	{
	  pedwarn_init ("excess elements in scalar initializer");
	  break;
	}
      else
	{
	  if (value.value)
	    output_init_element (value.value, strict_string,
				 constructor_type, NULL_TREE, 1);
	  constructor_fields = 0;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      if (constructor_range_stack)
	{
	  struct constructor_range_stack *p, *range_stack;
	  int finish = 0;

	  range_stack = constructor_range_stack;
	  constructor_range_stack = 0;
	  while (constructor_stack != range_stack->stack)
	    {
	      gcc_assert (constructor_stack->implicit);
	      process_init_element (pop_init_level (1));
	    }
	  for (p = range_stack;
	       !p->range_end || tree_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_stack->implicit);
	      process_init_element (pop_init_level (1));
	    }

	  p->index = size_binop (PLUS_EXPR, p->index, bitsize_one_node);
	  if (tree_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  while (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      if (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      if (!p)
		break;
	      push_init_level (2);
	      p->stack = constructor_stack;
	      if (p->range_end && tree_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  if (!finish)
	    constructor_range_stack = range_stack;
	  continue;
	}

      break;
    }

  constructor_range_stack = 0;
}
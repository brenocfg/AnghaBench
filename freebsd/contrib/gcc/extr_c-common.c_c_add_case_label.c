#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  splay_tree_value ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  TYPE_2__* splay_tree ;
struct TYPE_12__ {int /*<<< orphan*/  root; } ;
struct TYPE_11__ {scalar_t__ value; scalar_t__ key; } ;

/* Variables and functions */
 scalar_t__ CASE_HIGH (scalar_t__) ; 
 scalar_t__ CASE_LABEL (scalar_t__) ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_case_label (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  build_stmt (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  check_case_bounds (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ check_case_value (scalar_t__) ; 
 scalar_t__ convert_and_check (scalar_t__,scalar_t__) ; 
 scalar_t__ create_artificial_label () ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  splay_tree_insert (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* splay_tree_lookup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* splay_tree_predecessor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* splay_tree_successor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_int_cst_compare (scalar_t__,scalar_t__) ; 
 scalar_t__ tree_int_cst_equal (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tree_int_cst_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

tree
c_add_case_label (splay_tree cases, tree cond, tree orig_type,
		  tree low_value, tree high_value)
{
  tree type;
  tree label;
  tree case_label;
  splay_tree_node node;

  /* Create the LABEL_DECL itself.  */
  label = create_artificial_label ();

  /* If there was an error processing the switch condition, bail now
     before we get more confused.  */
  if (!cond || cond == error_mark_node)
    goto error_out;

  if ((low_value && TREE_TYPE (low_value)
       && POINTER_TYPE_P (TREE_TYPE (low_value)))
      || (high_value && TREE_TYPE (high_value)
	  && POINTER_TYPE_P (TREE_TYPE (high_value))))
    {
      error ("pointers are not permitted as case values");
      goto error_out;
    }

  /* Case ranges are a GNU extension.  */
  if (high_value && pedantic)
    pedwarn ("range expressions in switch statements are non-standard");

  type = TREE_TYPE (cond);
  if (low_value)
    {
      low_value = check_case_value (low_value);
      low_value = convert_and_check (type, low_value);
      if (low_value == error_mark_node)
	goto error_out;
    }
  if (high_value)
    {
      high_value = check_case_value (high_value);
      high_value = convert_and_check (type, high_value);
      if (high_value == error_mark_node)
	goto error_out;
    }

  if (low_value && high_value)
    {
      /* If the LOW_VALUE and HIGH_VALUE are the same, then this isn't
	 really a case range, even though it was written that way.
	 Remove the HIGH_VALUE to simplify later processing.  */
      if (tree_int_cst_equal (low_value, high_value))
	high_value = NULL_TREE;
      else if (!tree_int_cst_lt (low_value, high_value))
	warning (0, "empty range specified");
    }

  /* See if the case is in range of the type of the original testing
     expression.  If both low_value and high_value are out of range,
     don't insert the case label and return NULL_TREE.  */
  if (low_value
      && !check_case_bounds (type, orig_type,
			     &low_value, high_value ? &high_value : NULL))
    return NULL_TREE;

  /* Look up the LOW_VALUE in the table of case labels we already
     have.  */
  node = splay_tree_lookup (cases, (splay_tree_key) low_value);
  /* If there was not an exact match, check for overlapping ranges.
     There's no need to do this if there's no LOW_VALUE or HIGH_VALUE;
     that's a `default' label and the only overlap is an exact match.  */
  if (!node && (low_value || high_value))
    {
      splay_tree_node low_bound;
      splay_tree_node high_bound;

      /* Even though there wasn't an exact match, there might be an
	 overlap between this case range and another case range.
	 Since we've (inductively) not allowed any overlapping case
	 ranges, we simply need to find the greatest low case label
	 that is smaller that LOW_VALUE, and the smallest low case
	 label that is greater than LOW_VALUE.  If there is an overlap
	 it will occur in one of these two ranges.  */
      low_bound = splay_tree_predecessor (cases,
					  (splay_tree_key) low_value);
      high_bound = splay_tree_successor (cases,
					 (splay_tree_key) low_value);

      /* Check to see if the LOW_BOUND overlaps.  It is smaller than
	 the LOW_VALUE, so there is no need to check unless the
	 LOW_BOUND is in fact itself a case range.  */
      if (low_bound
	  && CASE_HIGH ((tree) low_bound->value)
	  && tree_int_cst_compare (CASE_HIGH ((tree) low_bound->value),
				    low_value) >= 0)
	node = low_bound;
      /* Check to see if the HIGH_BOUND overlaps.  The low end of that
	 range is bigger than the low end of the current range, so we
	 are only interested if the current range is a real range, and
	 not an ordinary case label.  */
      else if (high_bound
	       && high_value
	       && (tree_int_cst_compare ((tree) high_bound->key,
					 high_value)
		   <= 0))
	node = high_bound;
    }
  /* If there was an overlap, issue an error.  */
  if (node)
    {
      tree duplicate = CASE_LABEL ((tree) node->value);

      if (high_value)
	{
	  error ("duplicate (or overlapping) case value");
	  error ("%Jthis is the first entry overlapping that value", duplicate);
	}
      else if (low_value)
	{
	  error ("duplicate case value") ;
	  error ("%Jpreviously used here", duplicate);
	}
      else
	{
	  error ("multiple default labels in one switch");
	  error ("%Jthis is the first default label", duplicate);
	}
      goto error_out;
    }

  /* Add a CASE_LABEL to the statement-tree.  */
  case_label = add_stmt (build_case_label (low_value, high_value, label));
  /* Register this case label in the splay tree.  */
  splay_tree_insert (cases,
		     (splay_tree_key) low_value,
		     (splay_tree_value) case_label);

  return case_label;

 error_out:
  /* Add a label so that the back-end doesn't think that the beginning of
     the switch is unreachable.  Note that we do not add a case label, as
     that just leads to duplicates and thence to failure later on.  */
  if (!cases->root)
    {
      tree t = create_artificial_label ();
      add_stmt (build_stmt (LABEL_EXPR, t));
    }
  return error_mark_node;
}
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
typedef  void* tree ;
struct TYPE_3__ {void* value; scalar_t__ lattice_val; void* mem_ref; } ;
typedef  TYPE_1__ prop_value_t ;
typedef  scalar_t__ ccp_lattice_t ;

/* Variables and functions */
 scalar_t__ CONSTANT ; 
 void* NULL_TREE ; 
 scalar_t__ UNDEFINED ; 
 scalar_t__ UNKNOWN_VAL ; 
 scalar_t__ VARYING ; 
 void* ccp_fold (void*) ; 
 void* fold_const_aggregate_ref (void*) ; 
 int /*<<< orphan*/  fold_defer_overflow_warnings () ; 
 int /*<<< orphan*/  fold_undefer_overflow_warnings (int,void*,int /*<<< orphan*/ ) ; 
 void* get_rhs (void*) ; 
 scalar_t__ is_gimple_min_invariant (void*) ; 
 scalar_t__ likely_value (void*) ; 

__attribute__((used)) static prop_value_t
evaluate_stmt (tree stmt)
{
  prop_value_t val;
  tree simplified = NULL_TREE;
  ccp_lattice_t likelyvalue = likely_value (stmt);
  bool is_constant;

  val.mem_ref = NULL_TREE;

  fold_defer_overflow_warnings ();

  /* If the statement is likely to have a CONSTANT result, then try
     to fold the statement to determine the constant value.  */
  if (likelyvalue == CONSTANT)
    simplified = ccp_fold (stmt);
  /* If the statement is likely to have a VARYING result, then do not
     bother folding the statement.  */
  if (likelyvalue == VARYING)
    simplified = get_rhs (stmt);
  /* If the statement is an ARRAY_REF or COMPONENT_REF into constant
     aggregates, extract the referenced constant.  Otherwise the
     statement is likely to have an UNDEFINED value, and there will be
     nothing to do.  Note that fold_const_aggregate_ref returns
     NULL_TREE if the first case does not match.  */
  else if (!simplified)
    simplified = fold_const_aggregate_ref (get_rhs (stmt));

  is_constant = simplified && is_gimple_min_invariant (simplified);

  fold_undefer_overflow_warnings (is_constant, stmt, 0);

  if (is_constant)
    {
      /* The statement produced a constant value.  */
      val.lattice_val = CONSTANT;
      val.value = simplified;
    }
  else
    {
      /* The statement produced a nonconstant value.  If the statement
	 had UNDEFINED operands, then the result of the statement
	 should be UNDEFINED.  Otherwise, the statement is VARYING.  */
      if (likelyvalue == UNDEFINED || likelyvalue == UNKNOWN_VAL)
	val.lattice_val = likelyvalue;
      else
	val.lattice_val = VARYING;

      val.value = NULL_TREE;
    }

  return val;
}
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
struct data_reference {int dummy; } ;

/* Variables and functions */
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ DR_BASE_OBJECT (struct data_reference*) ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ array_ptr_differ_p (scalar_t__,scalar_t__,struct data_reference*) ; 
 scalar_t__ may_alias_p (scalar_t__,scalar_t__,struct data_reference*,struct data_reference*,int*) ; 
 scalar_t__ record_array_differ_p (struct data_reference*,struct data_reference*) ; 
 scalar_t__ record_ptr_differ_p (struct data_reference*,struct data_reference*) ; 
 scalar_t__ record_record_differ_p (struct data_reference*,struct data_reference*) ; 

__attribute__((used)) static bool
base_object_differ_p (struct data_reference *a,
		      struct data_reference *b,
		      bool *differ_p)
{
  tree base_a = DR_BASE_OBJECT (a);
  tree base_b = DR_BASE_OBJECT (b);
  bool aliased;

  if (!base_a || !base_b)
    return false;

  /* Determine if same base.  Example: for the array accesses
     a[i], b[i] or pointer accesses *a, *b, bases are a, b.  */
  if (base_a == base_b)
    {
      *differ_p = false;
      return true;
    }

  /* For pointer based accesses, (*p)[i], (*q)[j], the bases are (*p)
     and (*q)  */
  if (TREE_CODE (base_a) == INDIRECT_REF && TREE_CODE (base_b) == INDIRECT_REF
      && TREE_OPERAND (base_a, 0) == TREE_OPERAND (base_b, 0))
    {
      *differ_p = false;
      return true;
    }

  /* Record/union based accesses - s.a[i], t.b[j]. bases are s.a,t.b.  */ 
  if (TREE_CODE (base_a) == COMPONENT_REF && TREE_CODE (base_b) == COMPONENT_REF
      && TREE_OPERAND (base_a, 0) == TREE_OPERAND (base_b, 0)
      && TREE_OPERAND (base_a, 1) == TREE_OPERAND (base_b, 1))
    {
      *differ_p = false;
      return true;
    }


  /* Determine if different bases.  */

  /* At this point we know that base_a != base_b.  However, pointer
     accesses of the form x=(*p) and y=(*q), whose bases are p and q,
     may still be pointing to the same base. In SSAed GIMPLE p and q will
     be SSA_NAMES in this case.  Therefore, here we check if they are
     really two different declarations.  */
  if (TREE_CODE (base_a) == VAR_DECL && TREE_CODE (base_b) == VAR_DECL)
    {
      *differ_p = true;
      return true;
    }

  /* In case one of the bases is a pointer (a[i] and (*p)[i]), we check with the
     help of alias analysis that p is not pointing to a.  */
  if (array_ptr_differ_p (base_a, base_b, b) 
      || array_ptr_differ_p (base_b, base_a, a))
    {
      *differ_p = true;
      return true;
    }

  /* If the bases are pointers ((*q)[i] and (*p)[i]), we check with the
     help of alias analysis they don't point to the same bases.  */
  if (TREE_CODE (base_a) == INDIRECT_REF && TREE_CODE (base_b) == INDIRECT_REF 
      && (may_alias_p (TREE_OPERAND (base_a, 0), TREE_OPERAND (base_b, 0), a, b, 
		       &aliased)
	  && !aliased))
    {
      *differ_p = true;
      return true;
    }

  /* Compare two record/union bases s.a and t.b: s != t or (a != b and
     s and t are not unions).  */
  if (TREE_CODE (base_a) == COMPONENT_REF && TREE_CODE (base_b) == COMPONENT_REF
      && ((TREE_CODE (TREE_OPERAND (base_a, 0)) == VAR_DECL
           && TREE_CODE (TREE_OPERAND (base_b, 0)) == VAR_DECL
           && TREE_OPERAND (base_a, 0) != TREE_OPERAND (base_b, 0))
          || (TREE_CODE (TREE_TYPE (TREE_OPERAND (base_a, 0))) == RECORD_TYPE 
              && TREE_CODE (TREE_TYPE (TREE_OPERAND (base_b, 0))) == RECORD_TYPE
              && TREE_OPERAND (base_a, 1) != TREE_OPERAND (base_b, 1))))
    {
      *differ_p = true;
      return true;
    }

  /* Compare a record/union access (b.c[i] or p->c[i]) and a pointer
     ((*q)[i]).  */
  if (record_ptr_differ_p (a, b) || record_ptr_differ_p (b, a))
    {
      *differ_p = true;
      return true;
    }

  /* Compare a record/union access (b.c[i] or p->c[i]) and an array access 
     (a[i]). In case of p->c[i] use alias analysis to verify that p is not
     pointing to a.  */
  if (record_array_differ_p (a, b) || record_array_differ_p (b, a))
    {
      *differ_p = true;
      return true;
    }

  /* Compare two record/union accesses (b.c[i] or p->c[i]).  */
  if (record_record_differ_p (a, b))
    {
      *differ_p = true;
      return true;
    }

  return false;
}
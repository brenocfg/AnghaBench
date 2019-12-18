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
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ ARRAY_REF_TYPE ; 
 scalar_t__ DR_BASE_ADDRESS (struct data_reference*) ; 
 int /*<<< orphan*/  DR_IS_READ (struct data_reference*) ; 
 scalar_t__ DR_OFFSET (struct data_reference*) ; 
 scalar_t__ DR_TYPE (struct data_reference*) ; 
 scalar_t__ MULT_EXPR ; 
 scalar_t__ POINTER_REF_TYPE ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_RESTRICT (scalar_t__) ; 
 int base_object_differ_p (struct data_reference*,struct data_reference*,int*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ may_alias_p (scalar_t__,scalar_t__,struct data_reference*,struct data_reference*,int*) ; 

__attribute__((used)) static bool
base_addr_differ_p (struct data_reference *dra,
		    struct data_reference *drb,
		    bool *differ_p)
{
  tree addr_a = DR_BASE_ADDRESS (dra);
  tree addr_b = DR_BASE_ADDRESS (drb);
  tree type_a, type_b;
  bool aliased;

  if (!addr_a || !addr_b)
    return false;

  type_a = TREE_TYPE (addr_a);
  type_b = TREE_TYPE (addr_b);

  gcc_assert (POINTER_TYPE_P (type_a) &&  POINTER_TYPE_P (type_b));

  /* 1. if (both DRA and DRB are represented as arrays)
            compare DRA.BASE_OBJECT and DRB.BASE_OBJECT.  */
  if (DR_TYPE (dra) == ARRAY_REF_TYPE && DR_TYPE (drb) == ARRAY_REF_TYPE)
    return base_object_differ_p (dra, drb, differ_p);

  /* 2. else if (both DRA and DRB are represented as pointers)
	    try to prove that DRA.FIRST_LOCATION == DRB.FIRST_LOCATION.  */
  /* If base addresses are the same, we check the offsets, since the access of 
     the data-ref is described by {base addr + offset} and its access function,
     i.e., in order to decide whether the bases of data-refs are the same we 
     compare both base addresses and offsets.  */
  if (DR_TYPE (dra) == POINTER_REF_TYPE && DR_TYPE (drb) == POINTER_REF_TYPE
      && (addr_a == addr_b 
	  || (TREE_CODE (addr_a) == ADDR_EXPR && TREE_CODE (addr_b) == ADDR_EXPR
	      && TREE_OPERAND (addr_a, 0) == TREE_OPERAND (addr_b, 0))))
    {
      /* Compare offsets.  */
      tree offset_a = DR_OFFSET (dra); 
      tree offset_b = DR_OFFSET (drb);
      
      STRIP_NOPS (offset_a);
      STRIP_NOPS (offset_b);

      /* FORNOW: we only compare offsets that are MULT_EXPR, i.e., we don't handle
	 PLUS_EXPR.  */
      if (offset_a == offset_b
	  || (TREE_CODE (offset_a) == MULT_EXPR 
	      && TREE_CODE (offset_b) == MULT_EXPR
	      && TREE_OPERAND (offset_a, 0) == TREE_OPERAND (offset_b, 0)
	      && TREE_OPERAND (offset_a, 1) == TREE_OPERAND (offset_b, 1)))
	{
	  *differ_p = false;
	  return true;
	}
    }

  /*  3. else if (DRA and DRB are represented differently or 2. fails) 
              only try to prove that the bases are surely different.  */

  /* Apply alias analysis.  */
  if (may_alias_p (addr_a, addr_b, dra, drb, &aliased) && !aliased)
    {
      *differ_p = true;
      return true;
    }
  
  /* An instruction writing through a restricted pointer is "independent" of any 
     instruction reading or writing through a different pointer, in the same 
     block/scope.  */
  else if ((TYPE_RESTRICT (type_a) && !DR_IS_READ (dra))
      || (TYPE_RESTRICT (type_b) && !DR_IS_READ (drb)))
    {
      *differ_p = true;
      return true;
    }
  return false;
}
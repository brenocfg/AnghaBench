#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lattice_val; void* mem_ref; void* value; } ;
typedef  TYPE_1__ prop_value_t ;

/* Variables and functions */
 scalar_t__ CONSTANT ; 
 void* NULL_TREE ; 
 scalar_t__ UNDEFINED ; 
 scalar_t__ UNKNOWN_VAL ; 
 scalar_t__ VARYING ; 
 int /*<<< orphan*/  do_store_ccp ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_p (void*,void*,int /*<<< orphan*/ ) ; 
 int simple_cst_equal (void*,void*) ; 

__attribute__((used)) static void
ccp_lattice_meet (prop_value_t *val1, prop_value_t *val2)
{
  if (val1->lattice_val == UNDEFINED)
    {
      /* UNDEFINED M any = any   */
      *val1 = *val2;
    }
  else if (val2->lattice_val == UNDEFINED)
    {
      /* any M UNDEFINED = any
         Nothing to do.  VAL1 already contains the value we want.  */
      ;
    }
  else if (val1->lattice_val == UNKNOWN_VAL
           || val2->lattice_val == UNKNOWN_VAL)
    {
      /* UNKNOWN_VAL values are invalid if we are not doing STORE-CCP.  */
      gcc_assert (do_store_ccp);

      /* any M UNKNOWN_VAL = UNKNOWN_VAL.  */
      val1->lattice_val = UNKNOWN_VAL;
      val1->value = NULL_TREE;
      val1->mem_ref = NULL_TREE;
    }
  else if (val1->lattice_val == VARYING
           || val2->lattice_val == VARYING)
    {
      /* any M VARYING = VARYING.  */
      val1->lattice_val = VARYING;
      val1->value = NULL_TREE;
      val1->mem_ref = NULL_TREE;
    }
  else if (val1->lattice_val == CONSTANT
	   && val2->lattice_val == CONSTANT
	   && simple_cst_equal (val1->value, val2->value) == 1
	   && (!do_store_ccp
	       || (val1->mem_ref && val2->mem_ref
		   && operand_equal_p (val1->mem_ref, val2->mem_ref, 0))))
    {
      /* Ci M Cj = Ci		if (i == j)
	 Ci M Cj = VARYING	if (i != j)

         If these two values come from memory stores, make sure that
	 they come from the same memory reference.  */
      val1->lattice_val = CONSTANT;
      val1->value = val1->value;
      val1->mem_ref = val1->mem_ref;
    }
  else
    {
      /* Any other combination is VARYING.  */
      val1->lattice_val = VARYING;
      val1->value = NULL_TREE;
      val1->mem_ref = NULL_TREE;
    }
}
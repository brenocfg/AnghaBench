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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {void* lattice_val; int /*<<< orphan*/  mem_ref; scalar_t__ value; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ prop_value_t ;

/* Variables and functions */
 void* CONSTANT ; 
 scalar_t__ DECL_INITIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_EMPTY_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ MODIFY_EXPR ; 
 int /*<<< orphan*/  MTAG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ PHI_NODE ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_READONLY (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 void* UNDEFINED ; 
 int /*<<< orphan*/  UNINITIALIZED ; 
 void* UNKNOWN_VAL ; 
 void* VARYING ; 
 scalar_t__ ccp_decl_initial_min_invariant (scalar_t__) ; 
 scalar_t__ do_store_ccp ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 
 scalar_t__ is_gimple_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static prop_value_t
get_default_value (tree var)
{
  tree sym = SSA_NAME_VAR (var);
  prop_value_t val = { UNINITIALIZED, NULL_TREE, NULL_TREE };

  if (!do_store_ccp && !is_gimple_reg (var))
    {
      /* Short circuit for regular CCP.  We are not interested in any
	 non-register when DO_STORE_CCP is false.  */
      val.lattice_val = VARYING;
    }
  else if (SSA_NAME_VALUE (var)
	   && is_gimple_min_invariant (SSA_NAME_VALUE (var)))
    {
      val.lattice_val = CONSTANT;
      val.value = SSA_NAME_VALUE (var);
    }
  else if (TREE_STATIC (sym)
	   && TREE_READONLY (sym)
	   && !MTAG_P (sym)
	   && DECL_INITIAL (sym)
	   && ccp_decl_initial_min_invariant (DECL_INITIAL (sym)))
    {
      /* Globals and static variables declared 'const' take their
	 initial value.  */
      val.lattice_val = CONSTANT;
      val.value = DECL_INITIAL (sym);
      val.mem_ref = sym;
    }
  else
    {
      tree stmt = SSA_NAME_DEF_STMT (var);

      if (IS_EMPTY_STMT (stmt))
	{
	  /* Variables defined by an empty statement are those used
	     before being initialized.  If VAR is a local variable, we
	     can assume initially that it is UNDEFINED.  If we are
	     doing STORE-CCP, function arguments and non-register
	     variables are initially UNKNOWN_VAL, because we cannot
	     discard the value incoming from outside of this function
	     (see ccp_lattice_meet for details).  */
	  if (is_gimple_reg (sym) && TREE_CODE (sym) != PARM_DECL)
	    val.lattice_val = UNDEFINED;
	  else if (do_store_ccp)
	    val.lattice_val = UNKNOWN_VAL;
	  else
	    val.lattice_val = VARYING;
	}
      else if (TREE_CODE (stmt) == MODIFY_EXPR
	       || TREE_CODE (stmt) == PHI_NODE)
	{
	  /* Any other variable defined by an assignment or a PHI node
	     is considered UNDEFINED (or UNKNOWN_VAL if VAR is not a
	     GIMPLE register).  */
	  val.lattice_val = is_gimple_reg (sym) ? UNDEFINED : UNKNOWN_VAL;
	}
      else
	{
	  /* Otherwise, VAR will never take on a constant value.  */
	  val.lattice_val = VARYING;
	}
    }

  return val;
}
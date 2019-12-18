#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {scalar_t__ lattice_val; scalar_t__ value; scalar_t__ mem_ref; } ;
typedef  TYPE_1__ prop_value_t ;

/* Variables and functions */
 scalar_t__ CONSTANT ; 
 int TDF_DETAILS ; 
 scalar_t__ UNDEFINED ; 
 scalar_t__ UNKNOWN_VAL ; 
 scalar_t__ do_store_ccp ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  dump_lattice_value (scalar_t__,char*,TYPE_1__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* get_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
set_lattice_value (tree var, prop_value_t new_val)
{
  prop_value_t *old_val = get_value (var, false);

  /* Lattice transitions must always be monotonically increasing in
     value.  We allow two exceptions:
     
     1- If *OLD_VAL and NEW_VAL are the same, return false to
	inform the caller that this was a non-transition.

     2- If we are doing store-ccp (i.e., DOING_STORE_CCP is true),
	allow CONSTANT->UNKNOWN_VAL.  The UNKNOWN_VAL state is a
	special type of UNDEFINED state which prevents the short
	circuit evaluation of PHI arguments (see ccp_visit_phi_node
	and ccp_lattice_meet).  */
  gcc_assert (old_val->lattice_val <= new_val.lattice_val
              || (old_val->lattice_val == new_val.lattice_val
		  && old_val->value == new_val.value
		  && old_val->mem_ref == new_val.mem_ref)
	      || (do_store_ccp
		  && old_val->lattice_val == CONSTANT
		  && new_val.lattice_val == UNKNOWN_VAL));

  if (old_val->lattice_val != new_val.lattice_val)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  dump_lattice_value (dump_file, "Lattice value changed to ", new_val);
	  fprintf (dump_file, ".  %sdding SSA edges to worklist.\n",
	           new_val.lattice_val != UNDEFINED ? "A" : "Not a");
	}

      *old_val = new_val;

      /* Transitions UNINITIALIZED -> UNDEFINED are never interesting
	 for propagation purposes.  In these cases return false to
	 avoid doing useless work.  */
      return (new_val.lattice_val != UNDEFINED);
    }

  return false;
}
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
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  basic_block ;
typedef  int /*<<< orphan*/ * SSA_NAME_DEF_STMT ;

/* Variables and functions */
 int /*<<< orphan*/ * PHI_ARG_DEF (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * PHI_CHAIN (int /*<<< orphan*/ *) ; 
 unsigned int PHI_NUM_ARGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHI_RESULT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_PHI_ARG_DEF (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_phi_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * extract_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * get_component_ssa_name (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_complex_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * phi_nodes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_phi_components (basic_block bb)
{
  tree phi;

  for (phi = phi_nodes (bb); phi; phi = PHI_CHAIN (phi))
    if (is_complex_reg (PHI_RESULT (phi)))
      {
	tree lr, li, pr = NULL, pi = NULL;
	unsigned int i, n;

	lr = get_component_ssa_name (PHI_RESULT (phi), false);
	if (TREE_CODE (lr) == SSA_NAME)
	  {
	    pr = create_phi_node (lr, bb);
	    SSA_NAME_DEF_STMT (lr) = pr;
	  }

	li = get_component_ssa_name (PHI_RESULT (phi), true);
	if (TREE_CODE (li) == SSA_NAME)
	  {
	    pi = create_phi_node (li, bb);
	    SSA_NAME_DEF_STMT (li) = pi;
	  }
	
	for (i = 0, n = PHI_NUM_ARGS (phi); i < n; ++i)
	  {
	    tree comp, arg = PHI_ARG_DEF (phi, i);
	    if (pr)
	      {
		comp = extract_component (NULL, arg, false, false);
		SET_PHI_ARG_DEF (pr, i, comp);
	      }
	    if (pi)
	      {
		comp = extract_component (NULL, arg, true, false);
		SET_PHI_ARG_DEF (pi, i, comp);
	      }
	  }
      }
}
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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  t_bool ;
struct loop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHI_ARG_DEF (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ backedge_phi_arg_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  follow_ssa_edge (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t_false ; 

__attribute__((used)) static inline t_bool
follow_ssa_edge_in_condition_phi_branch (int i,
					 struct loop *loop, 
					 tree condition_phi, 
					 tree halting_phi,
					 tree *evolution_of_branch,
					 tree init_cond, int limit)
{
  tree branch = PHI_ARG_DEF (condition_phi, i);
  *evolution_of_branch = chrec_dont_know;

  /* Do not follow back edges (they must belong to an irreducible loop, which
     we really do not want to worry about).  */
  if (backedge_phi_arg_p (condition_phi, i))
    return t_false;

  if (TREE_CODE (branch) == SSA_NAME)
    {
      *evolution_of_branch = init_cond;
      return follow_ssa_edge (loop, SSA_NAME_DEF_STMT (branch), halting_phi, 
			      evolution_of_branch, limit);
    }

  /* This case occurs when one of the condition branches sets 
     the variable to a constant: i.e. a phi-node like
     "a_2 = PHI <a_7(5), 2(6)>;".  
	 
     FIXME:  This case have to be refined correctly: 
     in some cases it is possible to say something better than
     chrec_dont_know, for example using a wrap-around notation.  */
  return t_false;
}
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
struct loop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHI_ARG_DEF (int /*<<< orphan*/ ,int) ; 
 int PHI_NUM_ARGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analyze_scalar_evolution (struct loop*,int /*<<< orphan*/ ) ; 
 scalar_t__ backedge_phi_arg_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  chrec_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_not_analyzed_yet ; 

__attribute__((used)) static tree
interpret_condition_phi (struct loop *loop, tree condition_phi)
{
  int i;
  tree res = chrec_not_analyzed_yet;
  
  for (i = 0; i < PHI_NUM_ARGS (condition_phi); i++)
    {
      tree branch_chrec;
      
      if (backedge_phi_arg_p (condition_phi, i))
	{
	  res = chrec_dont_know;
	  break;
	}

      branch_chrec = analyze_scalar_evolution
	(loop, PHI_ARG_DEF (condition_phi, i));
      
      res = chrec_merge (res, branch_chrec);
    }

  return res;
}
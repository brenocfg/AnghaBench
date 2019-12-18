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
typedef  TYPE_1__* case_node_ptr ;
struct TYPE_4__ {struct TYPE_4__* parent; struct TYPE_4__* right; struct TYPE_4__* left; int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;

/* Variables and functions */
 scalar_t__ COST_TABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ use_cost_table ; 

__attribute__((used)) static void
balance_case_nodes (case_node_ptr *head, case_node_ptr parent)
{
  case_node_ptr np;

  np = *head;
  if (np)
    {
      int cost = 0;
      int i = 0;
      int ranges = 0;
      case_node_ptr *npp;
      case_node_ptr left;

      /* Count the number of entries on branch.  Also count the ranges.  */

      while (np)
	{
	  if (!tree_int_cst_equal (np->low, np->high))
	    {
	      ranges++;
	      if (use_cost_table)
		cost += COST_TABLE (TREE_INT_CST_LOW (np->high));
	    }

	  if (use_cost_table)
	    cost += COST_TABLE (TREE_INT_CST_LOW (np->low));

	  i++;
	  np = np->right;
	}

      if (i > 2)
	{
	  /* Split this list if it is long enough for that to help.  */
	  npp = head;
	  left = *npp;
	  if (use_cost_table)
	    {
	      /* Find the place in the list that bisects the list's total cost,
		 Here I gets half the total cost.  */
	      int n_moved = 0;
	      i = (cost + 1) / 2;
	      while (1)
		{
		  /* Skip nodes while their cost does not reach that amount.  */
		  if (!tree_int_cst_equal ((*npp)->low, (*npp)->high))
		    i -= COST_TABLE (TREE_INT_CST_LOW ((*npp)->high));
		  i -= COST_TABLE (TREE_INT_CST_LOW ((*npp)->low));
		  if (i <= 0)
		    break;
		  npp = &(*npp)->right;
		  n_moved += 1;
		}
	      if (n_moved == 0)
		{
		  /* Leave this branch lopsided, but optimize left-hand
		     side and fill in `parent' fields for right-hand side.  */
		  np = *head;
		  np->parent = parent;
		  balance_case_nodes (&np->left, np);
		  for (; np->right; np = np->right)
		    np->right->parent = np;
		  return;
		}
	    }
	  /* If there are just three nodes, split at the middle one.  */
	  else if (i == 3)
	    npp = &(*npp)->right;
	  else
	    {
	      /* Find the place in the list that bisects the list's total cost,
		 where ranges count as 2.
		 Here I gets half the total cost.  */
	      i = (i + ranges + 1) / 2;
	      while (1)
		{
		  /* Skip nodes while their cost does not reach that amount.  */
		  if (!tree_int_cst_equal ((*npp)->low, (*npp)->high))
		    i--;
		  i--;
		  if (i <= 0)
		    break;
		  npp = &(*npp)->right;
		}
	    }
	  *head = np = *npp;
	  *npp = 0;
	  np->parent = parent;
	  np->left = left;

	  /* Optimize each of the two split parts.  */
	  balance_case_nodes (&np->left, np);
	  balance_case_nodes (&np->right, np);
	}
      else
	{
	  /* Else leave this branch as one level,
	     but fill in `parent' fields.  */
	  np = *head;
	  np->parent = parent;
	  for (; np->right; np = np->right)
	    np->right->parent = np;
	}
    }
}
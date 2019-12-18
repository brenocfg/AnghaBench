#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {int /*<<< orphan*/  num_merged_labels; } ;

/* Variables and functions */
 scalar_t__ DECL_NONLOCAL (int /*<<< orphan*/ ) ; 
 scalar_t__ FORCED_LABEL (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR_LABEL (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 TYPE_1__ cfg_stats ; 

__attribute__((used)) static inline bool
stmt_starts_bb_p (tree t, tree prev_t)
{
  if (t == NULL_TREE)
    return false;

  /* LABEL_EXPRs start a new basic block only if the preceding
     statement wasn't a label of the same type.  This prevents the
     creation of consecutive blocks that have nothing but a single
     label.  */
  if (TREE_CODE (t) == LABEL_EXPR)
    {
      /* Nonlocal and computed GOTO targets always start a new block.  */
      if (DECL_NONLOCAL (LABEL_EXPR_LABEL (t))
	  || FORCED_LABEL (LABEL_EXPR_LABEL (t)))
	return true;

      if (prev_t && TREE_CODE (prev_t) == LABEL_EXPR)
	{
	  if (DECL_NONLOCAL (LABEL_EXPR_LABEL (prev_t)))
	    return true;

	  cfg_stats.num_merged_labels++;
	  return false;
	}
      else
	return true;
    }

  return false;
}
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
typedef  int /*<<< orphan*/  var_map ;
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  coalesce_list_p ;
struct TYPE_3__ {int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 TYPE_1__* EXIT_BLOCK_PTR ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 scalar_t__ RESULT_DECL ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_coalesce (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coalesce_cost (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  maybe_hot_bb_p (TYPE_1__*) ; 
 unsigned int num_var_partitions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * partition_to_var (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
coalesce_result_decls (var_map map, coalesce_list_p cl)
{
  unsigned int i, x;
  tree var = NULL;

  for (i = x = 0; x < num_var_partitions (map); x++)
    {
      tree p = partition_to_var (map, x);
      if (TREE_CODE (SSA_NAME_VAR (p)) == RESULT_DECL)
	{
	  if (var == NULL_TREE)
	    {
	      var = p;
	      i = x;
	    }
	  else
	    add_coalesce (cl, i, x,
			  coalesce_cost (EXIT_BLOCK_PTR->frequency,
					 maybe_hot_bb_p (EXIT_BLOCK_PTR),
					 false));
	}
    }
}
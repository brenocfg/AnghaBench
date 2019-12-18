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

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  import_export_decl (scalar_t__) ; 
 int /*<<< orphan*/  rest_of_decl_compilation (scalar_t__,int,int) ; 
 int /*<<< orphan*/  var_finalized_p (scalar_t__) ; 

__attribute__((used)) static void
write_out_vars (tree vars)
{
  tree v;

  for (v = vars; v; v = TREE_CHAIN (v))
    {
      tree var = TREE_VALUE (v);
      if (!var_finalized_p (var))
	{
	  import_export_decl (var);
	  rest_of_decl_compilation (var, 1, 1);
	}
    }
}
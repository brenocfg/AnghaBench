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

/* Variables and functions */
 int /*<<< orphan*/  DECL_ANON_UNION_ELEMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STATIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  anon_aggr_type_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_local_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_anon_union_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
c_expand_decl (tree decl)
{
  if (TREE_CODE (decl) == VAR_DECL && !TREE_STATIC (decl))
    {
      /* Let the back-end know about this variable.  */
      if (!anon_aggr_type_p (TREE_TYPE (decl)))
	emit_local_var (decl);
      else
	expand_anon_union_decl (decl, NULL_TREE,
				DECL_ANON_UNION_ELEMS (decl));
    }
  else
    return 0;

  return 1;
}
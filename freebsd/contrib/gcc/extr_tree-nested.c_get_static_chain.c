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
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  scalar_t__ tree ;
struct nesting_info {scalar_t__ context; struct nesting_info* outer; int /*<<< orphan*/  frame_decl; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPONENT_REF ; 
 int /*<<< orphan*/  INDIRECT_REF ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_addr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_chain_decl (struct nesting_info*) ; 
 scalar_t__ get_chain_field (struct nesting_info*) ; 
 scalar_t__ init_tmp_var (struct nesting_info*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
get_static_chain (struct nesting_info *info, tree target_context,
		  tree_stmt_iterator *tsi)
{
  struct nesting_info *i;
  tree x;

  if (info->context == target_context)
    {
      x = build_addr (info->frame_decl, target_context);
    }
  else
    {
      x = get_chain_decl (info);

      for (i = info->outer; i->context != target_context; i = i->outer)
	{
	  tree field = get_chain_field (i);

	  x = build1 (INDIRECT_REF, TREE_TYPE (TREE_TYPE (x)), x);
	  x = build3 (COMPONENT_REF, TREE_TYPE (field), x, field, NULL_TREE);
	  x = init_tmp_var (info, x, tsi);
	}
    }

  return x;
}
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
 scalar_t__ NAMESPACE_DECL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  ORIGINAL_NAMESPACE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decl_namespace_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decl_namespace_list ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
push_decl_namespace (tree decl)
{
  if (TREE_CODE (decl) != NAMESPACE_DECL)
    decl = decl_namespace_context (decl);
  decl_namespace_list = tree_cons (ORIGINAL_NAMESPACE (decl),
				   NULL_TREE, decl_namespace_list);
}
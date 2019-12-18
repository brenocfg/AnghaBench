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
 int /*<<< orphan*/  CP_DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_DECL (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 

tree
decl_namespace_context (tree decl)
{
  while (1)
    {
      if (TREE_CODE (decl) == NAMESPACE_DECL)
	return decl;
      else if (TYPE_P (decl))
	decl = CP_DECL_CONTEXT (TYPE_MAIN_DECL (decl));
      else
	decl = CP_DECL_CONTEXT (decl);
    }
}
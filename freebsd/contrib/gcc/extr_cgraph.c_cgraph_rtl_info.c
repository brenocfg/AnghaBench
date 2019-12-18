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
struct cgraph_rtl_info {int dummy; } ;
struct cgraph_node {struct cgraph_rtl_info rtl; int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  TREE_ASM_WRITTEN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 struct cgraph_node* cgraph_node (scalar_t__) ; 
 scalar_t__ current_function_decl ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

struct cgraph_rtl_info *
cgraph_rtl_info (tree decl)
{
  struct cgraph_node *node;

  gcc_assert (TREE_CODE (decl) == FUNCTION_DECL);
  node = cgraph_node (decl);
  if (decl != current_function_decl
      && !TREE_ASM_WRITTEN (node->decl))
    return NULL;
  return &node->rtl;
}
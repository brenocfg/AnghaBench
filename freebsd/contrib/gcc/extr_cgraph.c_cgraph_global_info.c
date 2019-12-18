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
struct cgraph_global_info {int dummy; } ;
struct cgraph_node {struct cgraph_global_info global; } ;

/* Variables and functions */
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ cgraph_global_info_ready ; 
 struct cgraph_node* cgraph_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

struct cgraph_global_info *
cgraph_global_info (tree decl)
{
  struct cgraph_node *node;

  gcc_assert (TREE_CODE (decl) == FUNCTION_DECL && cgraph_global_info_ready);
  node = cgraph_node (decl);
  return &node->global;
}
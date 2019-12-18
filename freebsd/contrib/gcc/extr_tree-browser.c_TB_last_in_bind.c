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
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TB_next_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
TB_last_in_bind (tree node)
{
  tree t;

  if (node == NULL_TREE)
    return NULL_TREE;

  while ((t = TB_next_expr (node)))
    node = t;

  return node;
}
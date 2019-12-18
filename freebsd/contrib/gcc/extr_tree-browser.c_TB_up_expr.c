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
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  TB_up_ht ; 
 scalar_t__ htab_find (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static tree
TB_up_expr (tree node)
{
  tree res;
  if (node == NULL_TREE)
    return NULL_TREE;

  res = (tree) htab_find (TB_up_ht, node);
  return res;
}
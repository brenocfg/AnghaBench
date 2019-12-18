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
typedef  int /*<<< orphan*/ * tree ;
typedef  TYPE_1__* splay_tree_node ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  reference_vars_to_consider ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree
get_static_decl (int index)
{
  splay_tree_node stn = 
    splay_tree_lookup (reference_vars_to_consider, index);
  if (stn)
    return (tree)stn->value;
  return NULL;
}
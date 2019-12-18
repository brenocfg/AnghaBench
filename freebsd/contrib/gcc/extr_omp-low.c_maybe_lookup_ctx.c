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
typedef  scalar_t__ tree ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  int /*<<< orphan*/  omp_context ;
struct TYPE_3__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_contexts ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static omp_context *
maybe_lookup_ctx (tree stmt)
{
  splay_tree_node n;
  n = splay_tree_lookup (all_contexts, (splay_tree_key) stmt);
  return n ? (omp_context *) n->value : NULL;
}
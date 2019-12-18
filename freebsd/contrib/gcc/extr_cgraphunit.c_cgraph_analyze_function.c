#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct TYPE_7__ {int /*<<< orphan*/  self_insns; scalar_t__ inlinable; int /*<<< orphan*/  disregard_inline_limits; } ;
struct TYPE_6__ {int /*<<< orphan*/  insns; } ;
struct cgraph_node {int analyzed; TYPE_3__ local; TYPE_2__ global; int /*<<< orphan*/ * decl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* disregard_inline_limits ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_1__ tree_inlining; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_STRUCT_FUNCTION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgraph_create_edges (struct cgraph_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgraph_lower_function (struct cgraph_node*) ; 
 int /*<<< orphan*/ * current_function_decl ; 
 int /*<<< orphan*/  estimate_num_insns (int /*<<< orphan*/ *) ; 
 scalar_t__ flag_really_no_inline ; 
 int /*<<< orphan*/  flag_unit_at_a_time ; 
 int /*<<< orphan*/  initialize_inline_failed (struct cgraph_node*) ; 
 TYPE_4__ lang_hooks ; 
 int /*<<< orphan*/  pop_cfun () ; 
 int /*<<< orphan*/  push_cfun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ tree_inlinable_function_p (int /*<<< orphan*/ *) ; 

void
cgraph_analyze_function (struct cgraph_node *node)
{
  tree decl = node->decl;

  current_function_decl = decl;
  push_cfun (DECL_STRUCT_FUNCTION (decl));
  cgraph_lower_function (node);

  /* First kill forward declaration so reverse inlining works properly.  */
  cgraph_create_edges (node, decl);

  node->local.inlinable = tree_inlinable_function_p (decl);
  if (!flag_unit_at_a_time)
    node->local.self_insns = estimate_num_insns (decl);
  if (node->local.inlinable)
    node->local.disregard_inline_limits
      = lang_hooks.tree_inlining.disregard_inline_limits (decl);
  initialize_inline_failed (node);
  if (flag_really_no_inline && !node->local.disregard_inline_limits)
    node->local.inlinable = 0;
  /* Inlining characteristics are maintained by the cgraph_mark_inline.  */
  node->global.insns = node->local.self_insns;

  node->analyzed = true;
  pop_cfun ();
  current_function_decl = NULL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_3__ {scalar_t__ (* auto_var_in_fn_p ) (scalar_t__,scalar_t__) ;} ;
struct TYPE_4__ {TYPE_1__ tree_inlining; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ get_base_address (int /*<<< orphan*/ ) ; 
 TYPE_2__ lang_hooks ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
self_inlining_addr_expr (tree value, tree fn)
{
  tree var;

  if (TREE_CODE (value) != ADDR_EXPR)
    return false;

  var = get_base_address (TREE_OPERAND (value, 0));

  return var && lang_hooks.tree_inlining.auto_var_in_fn_p (var, fn);
}
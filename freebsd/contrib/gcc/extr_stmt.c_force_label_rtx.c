#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct function {TYPE_1__* expr; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int /*<<< orphan*/  x_forced_labels; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOIDmode ; 
 struct function* cfun ; 
 scalar_t__ current_function_decl ; 
 scalar_t__ decl_function_context (scalar_t__) ; 
 struct function* find_function_data (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_rtx (scalar_t__) ; 

rtx
force_label_rtx (tree label)
{
  rtx ref = label_rtx (label);
  tree function = decl_function_context (label);
  struct function *p;

  gcc_assert (function);

  if (function != current_function_decl)
    p = find_function_data (function);
  else
    p = cfun;

  p->expr->x_forced_labels = gen_rtx_EXPR_LIST (VOIDmode, ref,
						p->expr->x_forced_labels);
  return ref;
}
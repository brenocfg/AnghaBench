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
 scalar_t__ TEMPLATE_DECL ; 
 int TFF_CLASS_KEY_OR_ENUM ; 
 int TFF_EXPR_IN_PARENS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dump_template_argument (tree arg, int flags)
{
  if (TYPE_P (arg) || TREE_CODE (arg) == TEMPLATE_DECL)
    dump_type (arg, flags & ~TFF_CLASS_KEY_OR_ENUM);
  else
    dump_expr (arg, (flags | TFF_EXPR_IN_PARENS) & ~TFF_CLASS_KEY_OR_ENUM);
}
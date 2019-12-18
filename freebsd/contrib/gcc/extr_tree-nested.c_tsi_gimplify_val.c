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
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  int /*<<< orphan*/  tree ;
struct nesting_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_tmp_var (struct nesting_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_gimple_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
tsi_gimplify_val (struct nesting_info *info, tree exp, tree_stmt_iterator *tsi)
{
  if (is_gimple_val (exp))
    return exp;
  else
    return init_tmp_var (info, exp, tsi);
}
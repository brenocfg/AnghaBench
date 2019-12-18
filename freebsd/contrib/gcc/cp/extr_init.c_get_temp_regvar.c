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
 int /*<<< orphan*/  INIT_EXPR ; 
 int /*<<< orphan*/  add_decl_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_modify_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_temporary_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_expr_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
get_temp_regvar (tree type, tree init)
{
  tree decl;

  decl = create_temporary_var (type);
  add_decl_expr (decl);

  finish_expr_stmt (build_modify_expr (decl, INIT_EXPR, init));

  return decl;
}
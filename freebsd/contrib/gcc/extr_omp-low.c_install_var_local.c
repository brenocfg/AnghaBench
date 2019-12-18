#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ omp_context ;

/* Variables and functions */
 int /*<<< orphan*/  insert_decl_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omp_copy_decl_1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static tree
install_var_local (tree var, omp_context *ctx)
{
  tree new_var = omp_copy_decl_1 (var, ctx);
  insert_decl_map (&ctx->cb, var, new_var);
  return new_var;
}
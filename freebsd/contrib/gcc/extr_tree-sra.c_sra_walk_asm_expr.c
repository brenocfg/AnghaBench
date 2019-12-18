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
struct sra_walk_fns {int dummy; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_INPUTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_OUTPUTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sra_walk_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct sra_walk_fns const*) ; 

__attribute__((used)) static void
sra_walk_asm_expr (tree expr, block_stmt_iterator *bsi,
		   const struct sra_walk_fns *fns)
{
  sra_walk_tree_list (ASM_INPUTS (expr), bsi, false, fns);
  sra_walk_tree_list (ASM_OUTPUTS (expr), bsi, true, fns);
}
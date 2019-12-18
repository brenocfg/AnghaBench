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
struct ivopts_data {int /*<<< orphan*/  current_loop; } ;
struct iv_use {int /*<<< orphan*/ * op_p; int /*<<< orphan*/  stmt; } ;
struct iv_cand {int dummy; } ;
struct affine_tree_combination {int dummy; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_ref_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_mem_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct affine_tree_combination*) ; 
 int /*<<< orphan*/  get_computation_aff (int /*<<< orphan*/ ,struct iv_use*,struct iv_cand*,int /*<<< orphan*/ ,struct affine_tree_combination*) ; 
 int /*<<< orphan*/  unshare_aff_combination (struct affine_tree_combination*) ; 

__attribute__((used)) static void
rewrite_use_address (struct ivopts_data *data,
		     struct iv_use *use, struct iv_cand *cand)
{
  struct affine_tree_combination aff;
  block_stmt_iterator bsi = bsi_for_stmt (use->stmt);
  tree ref;

  get_computation_aff (data->current_loop, use, cand, use->stmt, &aff);
  unshare_aff_combination (&aff);

  ref = create_mem_ref (&bsi, TREE_TYPE (*use->op_p), &aff);
  copy_ref_info (ref, *use->op_p);
  *use->op_p = ref;
}
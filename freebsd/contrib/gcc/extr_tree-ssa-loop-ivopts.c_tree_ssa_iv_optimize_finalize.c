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
struct ivopts_data {int /*<<< orphan*/  iv_candidates; int /*<<< orphan*/  iv_uses; int /*<<< orphan*/  niters; int /*<<< orphan*/  important_candidates; int /*<<< orphan*/  relevant; int /*<<< orphan*/  version_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decl_rtl_to_reset ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_loop_data (struct ivopts_data*) ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_cand_p ; 
 int /*<<< orphan*/  iv_use_p ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void
tree_ssa_iv_optimize_finalize (struct ivopts_data *data)
{
  free_loop_data (data);
  free (data->version_info);
  BITMAP_FREE (data->relevant);
  BITMAP_FREE (data->important_candidates);
  htab_delete (data->niters);

  VEC_free (tree, heap, decl_rtl_to_reset);
  VEC_free (iv_use_p, heap, data->iv_uses);
  VEC_free (iv_cand_p, heap, data->iv_candidates);
}
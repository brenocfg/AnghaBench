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
typedef  scalar_t__ tree ;
struct dse_global_data {int /*<<< orphan*/  stores; } ;
struct dse_block_local_data {int /*<<< orphan*/  stores; } ;
struct dom_walk_data {struct dse_global_data* global_data; int /*<<< orphan*/  block_data_stack; } ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  PHI_RESULT (scalar_t__) ; 
 struct dse_block_local_data* VEC_last (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_stmt_uid (scalar_t__) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_voperand_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_p ; 

__attribute__((used)) static void
dse_record_phis (struct dom_walk_data *walk_data, basic_block bb)
{
  struct dse_block_local_data *bd
    = VEC_last (void_p, walk_data->block_data_stack);
  struct dse_global_data *dse_gd = walk_data->global_data;
  tree phi;

  for (phi = phi_nodes (bb); phi; phi = PHI_CHAIN (phi))
    if (!is_gimple_reg (PHI_RESULT (phi)))
      record_voperand_set (dse_gd->stores,
			   &bd->stores,
			   get_stmt_uid (phi));
}
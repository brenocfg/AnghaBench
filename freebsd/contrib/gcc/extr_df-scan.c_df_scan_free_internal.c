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
struct df_scan_problem_data {int /*<<< orphan*/  mw_link_pool; int /*<<< orphan*/  mw_reg_pool; int /*<<< orphan*/  reg_pool; int /*<<< orphan*/  insn_pool; int /*<<< orphan*/  ref_pool; } ;
struct df_ref_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * refs; int /*<<< orphan*/ * regs; } ;
struct df {int /*<<< orphan*/  exit_block_uses; int /*<<< orphan*/  entry_block_defs; int /*<<< orphan*/  hardware_regs_used; scalar_t__ insns_size; int /*<<< orphan*/ * insns; TYPE_1__ use_info; TYPE_1__ def_info; } ;
struct dataflow {int /*<<< orphan*/  block_pool; scalar_t__ block_info_size; int /*<<< orphan*/ * block_info; scalar_t__ problem_data; struct df* df; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_alloc_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void 
df_scan_free_internal (struct dataflow *dflow)
{
  struct df *df = dflow->df;
  struct df_scan_problem_data *problem_data
    = (struct df_scan_problem_data *) dflow->problem_data;

  free (df->def_info.regs);
  free (df->def_info.refs);
  memset (&df->def_info, 0, (sizeof (struct df_ref_info)));

  free (df->use_info.regs);
  free (df->use_info.refs);
  memset (&df->use_info, 0, (sizeof (struct df_ref_info)));

  free (df->insns);
  df->insns = NULL;
  df->insns_size = 0;

  free (dflow->block_info);
  dflow->block_info = NULL;
  dflow->block_info_size = 0;

  BITMAP_FREE (df->hardware_regs_used);
  BITMAP_FREE (df->entry_block_defs);
  BITMAP_FREE (df->exit_block_uses);

  free_alloc_pool (dflow->block_pool);
  free_alloc_pool (problem_data->ref_pool);
  free_alloc_pool (problem_data->insn_pool);
  free_alloc_pool (problem_data->reg_pool);
  free_alloc_pool (problem_data->mw_reg_pool);
  free_alloc_pool (problem_data->mw_link_pool);
}
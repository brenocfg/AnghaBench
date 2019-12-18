#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct df_ref {int /*<<< orphan*/  id; int /*<<< orphan*/  reg; int /*<<< orphan*/  insn; } ;
struct df_rd_bb_info {int /*<<< orphan*/  gen; } ;
struct df {int dummy; } ;
typedef  TYPE_2__* ddg_ptr ;
typedef  TYPE_3__* ddg_node_ptr ;
struct TYPE_12__ {int cuid; } ;
struct TYPE_11__ {int num_nodes; TYPE_1__* nodes; int /*<<< orphan*/  bb; } ;
struct TYPE_10__ {int /*<<< orphan*/  insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANTI_DEP ; 
 struct df_rd_bb_info* DF_RD_BB_INFO (struct df*,int /*<<< orphan*/ ) ; 
 int DF_REF_REGNO (struct df_ref*) ; 
 int /*<<< orphan*/  REG_DEP ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ddg_dep_no_link (TYPE_2__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct df_ref* df_bb_regno_first_def_find (struct df*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ df_find_def (struct df*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_3__* get_node_of_insn (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_deps_for_use (ddg_ptr g, struct df *df, struct df_ref *use)
{
  int i;
  int regno = DF_REF_REGNO (use);
  struct df_ref *first_def = df_bb_regno_first_def_find (df, g->bb, regno);
  ddg_node_ptr use_node;
  ddg_node_ptr def_node;
  struct df_rd_bb_info *bb_info;

  bb_info = DF_RD_BB_INFO (df, g->bb);

  if (!first_def)
    return;

  use_node = get_node_of_insn (g, use->insn);
  def_node = get_node_of_insn (g, first_def->insn);

  gcc_assert (use_node && def_node);

  /* Make sure there are no defs after USE.  */
  for (i = use_node->cuid + 1; i < g->num_nodes; i++)
     if (df_find_def (df, g->nodes[i].insn, use->reg))
       return;
  /* We must not add ANTI dep when there is an intra-loop TRUE dep in
     the opposite direction. If the first_def reaches the USE then there is
     such a dep.  */
  if (! bitmap_bit_p (bb_info->gen, first_def->id))
    create_ddg_dep_no_link (g, use_node, def_node, ANTI_DEP, REG_DEP, 1);
}
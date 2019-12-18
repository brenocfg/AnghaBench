#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  scalar_t__ dep_type ;
typedef  int /*<<< orphan*/  dep_data_type ;
typedef  int /*<<< orphan*/  ddg_ptr ;
typedef  TYPE_1__* ddg_node_ptr ;
typedef  int /*<<< orphan*/  ddg_edge_ptr ;
struct TYPE_6__ {int /*<<< orphan*/  insn; } ;

/* Variables and functions */
 scalar_t__ ANTI_DEP ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ OUTPUT_DEP ; 
 int /*<<< orphan*/  PUT_REG_NOTE_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_DEP_ANTI ; 
 int /*<<< orphan*/  REG_DEP_OUTPUT ; 
 int /*<<< orphan*/  add_backarc_to_ddg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_edge_to_ddg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_INSN_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ddg_edge (TYPE_1__*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  free_INSN_LIST_node (int /*<<< orphan*/ ) ; 
 int insn_cost (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
create_ddg_dep_no_link (ddg_ptr g, ddg_node_ptr from, ddg_node_ptr to,
			dep_type d_t, dep_data_type d_dt, int distance)
{
  ddg_edge_ptr e;
  int l;
  rtx link = alloc_INSN_LIST (to->insn, NULL_RTX);

  if (d_t == ANTI_DEP)
    PUT_REG_NOTE_KIND (link, REG_DEP_ANTI);
  else if (d_t == OUTPUT_DEP)
    PUT_REG_NOTE_KIND (link, REG_DEP_OUTPUT);

  l = insn_cost (from->insn, link, to->insn);
  free_INSN_LIST_node (link);

  e = create_ddg_edge (from, to, d_t, d_dt, l, distance);
  if (distance > 0)
    add_backarc_to_ddg (g, e);
  else
    add_edge_to_ddg (g, e);
}
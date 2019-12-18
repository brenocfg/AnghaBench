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
struct loop {int dummy; } ;
typedef  int /*<<< orphan*/  loop_vec_info ;
typedef  int /*<<< orphan*/  edge ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 struct loop* LOOP_VINFO_LOOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOP_VINFO_NITERS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  add_referenced_var (scalar_t__) ; 
 int /*<<< orphan*/  bsi_insert_on_edge_immediate (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ create_tmp_var (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ force_gimple_operand (scalar_t__,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  loop_preheader_edge (struct loop*) ; 
 scalar_t__ unshare_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
vect_build_loop_niters (loop_vec_info loop_vinfo)
{
  tree ni_name, stmt, var;
  edge pe;
  struct loop *loop = LOOP_VINFO_LOOP (loop_vinfo);
  tree ni = unshare_expr (LOOP_VINFO_NITERS (loop_vinfo));

  var = create_tmp_var (TREE_TYPE (ni), "niters");
  add_referenced_var (var);
  ni_name = force_gimple_operand (ni, &stmt, false, var);

  pe = loop_preheader_edge (loop);
  if (stmt)
    {
      basic_block new_bb = bsi_insert_on_edge_immediate (pe, stmt);
      gcc_assert (!new_bb);
    }
      
  return ni_name;
}
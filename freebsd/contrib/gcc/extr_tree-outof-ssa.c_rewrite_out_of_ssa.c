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
typedef  int /*<<< orphan*/  var_map ;

/* Variables and functions */
 int SSANORM_COALESCE_PARTITIONS ; 
 int SSANORM_COMBINE_TEMPS ; 
 int SSANORM_PERFORM_TER ; 
 int SSA_VAR_MAP_REF_COUNT ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  create_ssa_var_map (int) ; 
 int /*<<< orphan*/  delete_var_map (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  dump_tree_cfg (scalar_t__,int) ; 
 int /*<<< orphan*/  eliminate_virtual_phis () ; 
 int /*<<< orphan*/  flag_mudflap ; 
 scalar_t__ flag_tree_combine_temps ; 
 int /*<<< orphan*/  flag_tree_live_range_split ; 
 scalar_t__ flag_tree_ter ; 
 int in_ssa_p ; 
 int /*<<< orphan*/  insert_backedge_copies () ; 
 int /*<<< orphan*/  remove_ssa_form (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int
rewrite_out_of_ssa (void)
{
  var_map map;
  int var_flags = 0;
  int ssa_flags = 0;

  /* If elimination of a PHI requires inserting a copy on a backedge,
     then we will have to split the backedge which has numerous
     undesirable performance effects.

     A significant number of such cases can be handled here by inserting
     copies into the loop itself.  */
  insert_backedge_copies ();

  if (!flag_tree_live_range_split)
    ssa_flags |= SSANORM_COALESCE_PARTITIONS;
    
  eliminate_virtual_phis ();

  if (dump_file && (dump_flags & TDF_DETAILS))
    dump_tree_cfg (dump_file, dump_flags & ~TDF_DETAILS);

  /* We cannot allow unssa to un-gimplify trees before we instrument them.  */
  if (flag_tree_ter && !flag_mudflap)
    var_flags = SSA_VAR_MAP_REF_COUNT;

  map = create_ssa_var_map (var_flags);

  if (flag_tree_combine_temps)
    ssa_flags |= SSANORM_COMBINE_TEMPS;
  if (flag_tree_ter && !flag_mudflap)
    ssa_flags |= SSANORM_PERFORM_TER;

  remove_ssa_form (map, ssa_flags);

  if (dump_file && (dump_flags & TDF_DETAILS))
    dump_tree_cfg (dump_file, dump_flags & ~TDF_DETAILS);

  /* Flush out flow graph and SSA data.  */
  delete_var_map (map);

  in_ssa_p = false;
  return 0;
}
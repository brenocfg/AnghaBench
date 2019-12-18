#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_8__ {int n_bits; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_total_mappings; int /*<<< orphan*/  num_virtual_symbols; int /*<<< orphan*/  virtual_symbols; int /*<<< orphan*/  num_virtual_mappings; } ;

/* Variables and functions */
 size_t DECL_UID (scalar_t__) ; 
 int NAME_SETS_GROWTH_FACTOR ; 
 int /*<<< orphan*/  SET_BIT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME_VAR (scalar_t__) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (scalar_t__) ; 
 int /*<<< orphan*/  TV_TREE_SSA_INCREMENTAL ; 
 int /*<<< orphan*/  add_to_repl_tbl (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bitmap_ior_into (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  is_gimple_reg (scalar_t__) ; 
 scalar_t__ is_new_name (scalar_t__) ; 
 int /*<<< orphan*/  names_replaced_by (scalar_t__) ; 
 int need_to_update_vops_p ; 
 TYPE_2__* new_ssa_names ; 
 int num_ssa_names ; 
 TYPE_2__* old_ssa_names ; 
 TYPE_2__* sbitmap_resize (TYPE_2__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 TYPE_1__ update_ssa_stats ; 

__attribute__((used)) static void
add_new_name_mapping (tree new, tree old)
{
  timevar_push (TV_TREE_SSA_INCREMENTAL);

  /* OLD and NEW must be different SSA names for the same symbol.  */
  gcc_assert (new != old && SSA_NAME_VAR (new) == SSA_NAME_VAR (old));

  /* We may need to grow NEW_SSA_NAMES and OLD_SSA_NAMES because our
     caller may have created new names since the set was created.  */
  if (new_ssa_names->n_bits <= num_ssa_names - 1)
    {
      unsigned int new_sz = num_ssa_names + NAME_SETS_GROWTH_FACTOR;
      new_ssa_names = sbitmap_resize (new_ssa_names, new_sz, 0);
      old_ssa_names = sbitmap_resize (old_ssa_names, new_sz, 0);
    }

  /* If this mapping is for virtual names, we will need to update
     virtual operands.  */
  if (!is_gimple_reg (new))
    {
      tree sym;
      size_t uid;

      need_to_update_vops_p = true;

      /* Keep counts of virtual mappings and symbols to use in the
	 virtual mapping heuristic.  If we have large numbers of
	 virtual mappings for a relatively low number of symbols, it
	 will make more sense to rename the symbols from scratch.
	 Otherwise, the insertion of PHI nodes for each of the old
	 names in these mappings will be very slow.  */
      sym = SSA_NAME_VAR (new);
      uid = DECL_UID (sym);
      update_ssa_stats.num_virtual_mappings++;
      if (!bitmap_bit_p (update_ssa_stats.virtual_symbols, uid))
	{
	  bitmap_set_bit (update_ssa_stats.virtual_symbols, uid);
	  update_ssa_stats.num_virtual_symbols++;
	}
    }

  /* Update the REPL_TBL table.  */
  add_to_repl_tbl (new, old);

  /* If OLD had already been registered as a new name, then all the
     names that OLD replaces should also be replaced by NEW.  */
  if (is_new_name (old))
    bitmap_ior_into (names_replaced_by (new), names_replaced_by (old));

  /* Register NEW and OLD in NEW_SSA_NAMES and OLD_SSA_NAMES,
     respectively.  */
  SET_BIT (new_ssa_names, SSA_NAME_VERSION (new));
  SET_BIT (old_ssa_names, SSA_NAME_VERSION (old));

  /* Update mapping counter to use in the virtual mapping heuristic.  */
  update_ssa_stats.num_total_mappings++;

  timevar_pop (TV_TREE_SSA_INCREMENTAL);
}
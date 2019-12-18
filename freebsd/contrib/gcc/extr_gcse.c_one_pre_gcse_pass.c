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
struct TYPE_6__ {scalar_t__ n_elems; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_noreturn_fake_exit_edges () ; 
 int /*<<< orphan*/  alloc_hash_table (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_pre_mem (int /*<<< orphan*/ ,scalar_t__) ; 
 int bytes_used ; 
 int /*<<< orphan*/  compute_hash_table (TYPE_1__*) ; 
 int /*<<< orphan*/  compute_ld_motion_mems () ; 
 int /*<<< orphan*/  compute_pre_data () ; 
 char* current_function_name () ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_hash_table (scalar_t__,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  edge_list ; 
 TYPE_1__ expr_hash_table ; 
 scalar_t__ flag_gcse_lm ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  free_edge_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_hash_table (TYPE_1__*) ; 
 int /*<<< orphan*/  free_ldst_mems () ; 
 int /*<<< orphan*/  free_pre_mem () ; 
 int gcse_create_count ; 
 int gcse_subst_count ; 
 int /*<<< orphan*/  last_basic_block ; 
 int /*<<< orphan*/  max_cuid ; 
 int pre_gcse () ; 
 int /*<<< orphan*/  remove_fake_exit_edges () ; 
 int /*<<< orphan*/  trim_ld_motion_mems () ; 

__attribute__((used)) static int
one_pre_gcse_pass (int pass)
{
  int changed = 0;

  gcse_subst_count = 0;
  gcse_create_count = 0;

  alloc_hash_table (max_cuid, &expr_hash_table, 0);
  add_noreturn_fake_exit_edges ();
  if (flag_gcse_lm)
    compute_ld_motion_mems ();

  compute_hash_table (&expr_hash_table);
  trim_ld_motion_mems ();
  if (dump_file)
    dump_hash_table (dump_file, "Expression", &expr_hash_table);

  if (expr_hash_table.n_elems > 0)
    {
      alloc_pre_mem (last_basic_block, expr_hash_table.n_elems);
      compute_pre_data ();
      changed |= pre_gcse ();
      free_edge_list (edge_list);
      free_pre_mem ();
    }

  free_ldst_mems ();
  remove_fake_exit_edges ();
  free_hash_table (&expr_hash_table);

  if (dump_file)
    {
      fprintf (dump_file, "\nPRE GCSE of %s, pass %d: %d bytes needed, ",
	       current_function_name (), pass, bytes_used);
      fprintf (dump_file, "%d substs, %d insns created\n",
	       gcse_subst_count, gcse_create_count);
    }

  return changed;
}
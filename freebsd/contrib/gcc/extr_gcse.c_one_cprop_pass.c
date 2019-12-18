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
 int /*<<< orphan*/ * XCNEWVEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_cprop_mem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  alloc_hash_table (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int bypass_conditional_jumps () ; 
 int bytes_used ; 
 int /*<<< orphan*/  compute_cprop_data () ; 
 int /*<<< orphan*/  compute_hash_table (TYPE_1__*) ; 
 int cprop (int) ; 
 char* current_function_name () ; 
 int /*<<< orphan*/  delete_unreachable_blocks () ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_hash_table (scalar_t__,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  find_implicit_sets () ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_cprop_mem () ; 
 int /*<<< orphan*/  free_hash_table (TYPE_1__*) ; 
 int global_const_prop_count ; 
 int global_copy_prop_count ; 
 int /*<<< orphan*/ * implicit_sets ; 
 int /*<<< orphan*/  last_basic_block ; 
 int local_const_prop_count ; 
 int local_copy_prop_count ; 
 int /*<<< orphan*/  local_cprop_pass (int) ; 
 int /*<<< orphan*/  max_cuid ; 
 int /*<<< orphan*/  rtx ; 
 TYPE_1__ set_hash_table ; 

__attribute__((used)) static int
one_cprop_pass (int pass, bool cprop_jumps, bool bypass_jumps)
{
  int changed = 0;

  global_const_prop_count = local_const_prop_count = 0;
  global_copy_prop_count = local_copy_prop_count = 0;

  local_cprop_pass (cprop_jumps);

  /* Determine implicit sets.  */
  implicit_sets = XCNEWVEC (rtx, last_basic_block);
  find_implicit_sets ();

  alloc_hash_table (max_cuid, &set_hash_table, 1);
  compute_hash_table (&set_hash_table);

  /* Free implicit_sets before peak usage.  */
  free (implicit_sets);
  implicit_sets = NULL;

  if (dump_file)
    dump_hash_table (dump_file, "SET", &set_hash_table);
  if (set_hash_table.n_elems > 0)
    {
      alloc_cprop_mem (last_basic_block, set_hash_table.n_elems);
      compute_cprop_data ();
      changed = cprop (cprop_jumps);
      if (bypass_jumps)
	changed |= bypass_conditional_jumps ();
      free_cprop_mem ();
    }

  free_hash_table (&set_hash_table);

  if (dump_file)
    {
      fprintf (dump_file, "CPROP of %s, pass %d: %d bytes needed, ",
	       current_function_name (), pass, bytes_used);
      fprintf (dump_file, "%d local const props, %d local copy props, ",
	       local_const_prop_count, local_copy_prop_count);
      fprintf (dump_file, "%d global const props, %d global copy props\n\n",
	       global_const_prop_count, global_copy_prop_count);
    }
  /* Global analysis may get into infinite loops for unreachable blocks.  */
  if (changed && cprop_jumps)
    delete_unreachable_blocks ();

  return changed;
}
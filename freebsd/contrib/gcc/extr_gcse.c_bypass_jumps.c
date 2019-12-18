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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAX_GCSE_PASSES ; 
 scalar_t__ NUM_FIXED_BLOCKS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  alloc_gcse_mem () ; 
 int /*<<< orphan*/  alloc_reg_set_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allocate_reg_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bytes_used ; 
 int /*<<< orphan*/  compute_sets () ; 
 scalar_t__ current_function_calls_setjmp ; 
 char* current_function_name () ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  dump_flow_info (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_alias_analysis () ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  free_gcse_mem () ; 
 int /*<<< orphan*/  free_reg_set_mem () ; 
 int /*<<< orphan*/  gcc_obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcse_obstack ; 
 int /*<<< orphan*/  init_alias_analysis () ; 
 scalar_t__ is_too_expensive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_gcse_regno ; 
 int /*<<< orphan*/  max_reg_num () ; 
 scalar_t__ n_basic_blocks ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int one_cprop_pass (scalar_t__,int,int) ; 

__attribute__((used)) static int
bypass_jumps (void)
{
  int changed;

  /* We do not construct an accurate cfg in functions which call
     setjmp, so just punt to be safe.  */
  if (current_function_calls_setjmp)
    return 0;

  /* Identify the basic block information for this function, including
     successors and predecessors.  */
  max_gcse_regno = max_reg_num ();

  if (dump_file)
    dump_flow_info (dump_file, dump_flags);

  /* Return if there's nothing to do, or it is too expensive.  */
  if (n_basic_blocks <= NUM_FIXED_BLOCKS + 1
      || is_too_expensive (_ ("jump bypassing disabled")))
    return 0;

  gcc_obstack_init (&gcse_obstack);
  bytes_used = 0;

  /* We need alias.  */
  init_alias_analysis ();

  /* Record where pseudo-registers are set.  This data is kept accurate
     during each pass.  ??? We could also record hard-reg information here
     [since it's unchanging], however it is currently done during hash table
     computation.

     It may be tempting to compute MEM set information here too, but MEM sets
     will be subject to code motion one day and thus we need to compute
     information about memory sets when we build the hash tables.  */

  alloc_reg_set_mem (max_gcse_regno);
  compute_sets ();

  max_gcse_regno = max_reg_num ();
  alloc_gcse_mem ();
  changed = one_cprop_pass (MAX_GCSE_PASSES + 2, true, true);
  free_gcse_mem ();

  if (dump_file)
    {
      fprintf (dump_file, "BYPASS of %s: %d basic blocks, ",
	       current_function_name (), n_basic_blocks);
      fprintf (dump_file, "%d bytes\n\n", bytes_used);
    }

  obstack_free (&gcse_obstack, NULL);
  free_reg_set_mem ();

  /* We are finished with alias.  */
  end_alias_analysis ();
  allocate_reg_info (max_reg_num (), FALSE, FALSE);

  return changed;
}
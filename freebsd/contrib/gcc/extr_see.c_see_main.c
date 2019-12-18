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
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  htab_traverse (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_recog () ; 
 int last_bb ; 
 scalar_t__* see_bb_hash_ar ; 
 int /*<<< orphan*/  see_commit_changes () ; 
 int /*<<< orphan*/  see_execute_LCM () ; 
 int /*<<< orphan*/  see_free_data_structures () ; 
 int /*<<< orphan*/  see_initialize_data_structures () ; 
 int /*<<< orphan*/  see_merge_and_eliminate_extensions () ; 
 scalar_t__ see_pre_extension_hash ; 
 int /*<<< orphan*/  see_print_pre_extension_expr ; 
 int /*<<< orphan*/  see_print_register_properties ; 
 int see_propagate_extensions_to_uses () ; 

__attribute__((used)) static void
see_main (void)
{
  bool cont = false;
  int i = 0;

  /* Initialize global data structures.  */
  see_initialize_data_structures ();

  /* Phase 1: Propagate extensions to uses.  */
  cont = see_propagate_extensions_to_uses ();

  if (cont)
    {
      init_recog ();

      /* Phase 2: Merge and eliminate locally redundant extensions.  */
      see_merge_and_eliminate_extensions ();

      /* Phase 3: Eliminate globally redundant extensions.  */
      see_execute_LCM ();

      /* Phase 4: Commit changes to the insn stream.  */
      see_commit_changes ();

      if (dump_file)
	{
	  /* For debug purpose only.  */
	  fprintf (dump_file, "see_pre_extension_hash:\n");
	  htab_traverse (see_pre_extension_hash, see_print_pre_extension_expr,
      			 NULL);

	  for (i = 0; i < last_bb; i++)
	    {
 	      if (see_bb_hash_ar[i])
		/* Traverse over all the references in the basic block in
		   forward order.  */
		{
		  fprintf (dump_file,
			   "Searching register properties in bb %d\n", i);
		  htab_traverse (see_bb_hash_ar[i],
		  		 see_print_register_properties, NULL);
		}
	    }
	}
    }

  /* Free global data structures.  */
  see_free_data_structures ();
}
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
struct TYPE_2__ {int /*<<< orphan*/  (* finish ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  asm_file_name ; 
 scalar_t__ asm_out_file ; 
 scalar_t__ aux_info_file ; 
 int /*<<< orphan*/  aux_info_file_name ; 
 int /*<<< orphan*/  dump_alloc_pool_statistics () ; 
 int /*<<< orphan*/  dump_ggc_loc_statistics () ; 
 int /*<<< orphan*/  dump_rtx_statistics () ; 
 int /*<<< orphan*/  dump_tree_statistics () ; 
 int /*<<< orphan*/  dump_varray_statistics () ; 
 scalar_t__ errorcount ; 
 int /*<<< orphan*/  fatal_error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (scalar_t__) ; 
 scalar_t__ ferror (scalar_t__) ; 
 int /*<<< orphan*/  finish_optimization_passes () ; 
 scalar_t__ flag_gen_aux_info ; 
 int /*<<< orphan*/  free_reg_info () ; 
 int /*<<< orphan*/  ggc_print_statistics () ; 
 TYPE_1__ lang_hooks ; 
 scalar_t__ mem_report ; 
 int /*<<< orphan*/  stringpool_statistics () ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
finalize (void)
{
  /* Close the dump files.  */
  if (flag_gen_aux_info)
    {
      fclose (aux_info_file);
      if (errorcount)
	unlink (aux_info_file_name);
    }

  /* Close non-debugging input and output files.  Take special care to note
     whether fclose returns an error, since the pages might still be on the
     buffer chain while the file is open.  */

  if (asm_out_file)
    {
      if (ferror (asm_out_file) != 0)
	fatal_error ("error writing to %s: %m", asm_file_name);
      if (fclose (asm_out_file) != 0)
	fatal_error ("error closing %s: %m", asm_file_name);
    }

  finish_optimization_passes ();

  if (mem_report)
    {
      ggc_print_statistics ();
      stringpool_statistics ();
      dump_tree_statistics ();
      dump_rtx_statistics ();
      dump_varray_statistics ();
      dump_alloc_pool_statistics ();
      dump_ggc_loc_statistics ();
    }

  /* Free up memory for the benefit of leak detectors.  */
  free_reg_info ();

  /* Language-specific end of compilation actions.  */
  lang_hooks.finish ();
}
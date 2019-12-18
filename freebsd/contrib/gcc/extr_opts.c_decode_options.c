#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int (* init_options ) (unsigned int,char const**) ;int /*<<< orphan*/  (* initialize_diagnostics ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ unwind_tables_default; int /*<<< orphan*/  have_named_sections; int /*<<< orphan*/  default_target_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SIGNED_CHAR ; 
 int /*<<< orphan*/  OPTIMIZATION_OPTIONS (int,int) ; 
 int /*<<< orphan*/  OPT_Wuninitialized ; 
 int align_functions ; 
 int align_jumps ; 
 int align_labels ; 
 int align_loops ; 
 int flag_caller_saves ; 
 int flag_cprop_registers ; 
 int flag_crossjumping ; 
 int flag_cse_follow_jumps ; 
 int flag_cse_skip_blocks ; 
 int flag_defer_pop ; 
 int flag_delayed_branch ; 
 int flag_delete_null_pointer_checks ; 
 scalar_t__ flag_exceptions ; 
 int flag_expensive_optimizations ; 
 int flag_gcse ; 
 int flag_gcse_after_reload ; 
 int flag_guess_branch_prob ; 
 int flag_if_conversion ; 
 int flag_if_conversion2 ; 
 int flag_inline_functions ; 
 int flag_ipa_pure_const ; 
 int flag_ipa_reference ; 
 int flag_ipa_type_escape ; 
 scalar_t__ flag_merge_constants ; 
 int flag_no_inline ; 
 int flag_omit_frame_pointer ; 
 int flag_optimize_sibling_calls ; 
 int flag_peephole2 ; 
 scalar_t__ flag_pic ; 
 scalar_t__ flag_pie ; 
 int flag_really_no_inline ; 
 int flag_regmove ; 
 int flag_reorder_blocks ; 
 scalar_t__ flag_reorder_blocks_and_partition ; 
 int flag_reorder_functions ; 
 int flag_rerun_cse_after_loop ; 
 int flag_schedule_insns ; 
 int flag_schedule_insns_after_reload ; 
 int flag_shlib ; 
 int flag_short_enums ; 
 int /*<<< orphan*/  flag_signed_char ; 
 int flag_strict_aliasing ; 
 int flag_strict_overflow ; 
 int flag_thread_jumps ; 
 int flag_tree_ccp ; 
 int flag_tree_ch ; 
 int flag_tree_copy_prop ; 
 int flag_tree_copyrename ; 
 int flag_tree_dce ; 
 int flag_tree_dom ; 
 int flag_tree_dse ; 
 int flag_tree_fre ; 
 int flag_tree_live_range_split ; 
 int flag_tree_pre ; 
 int flag_tree_salias ; 
 int flag_tree_sink ; 
 int flag_tree_sra ; 
 int flag_tree_store_ccp ; 
 int flag_tree_store_copy_prop ; 
 int flag_tree_ter ; 
 int flag_unit_at_a_time ; 
 int flag_unswitch_loops ; 
 scalar_t__ flag_unwind_tables ; 
 int /*<<< orphan*/  global_dc ; 
 int /*<<< orphan*/  handle_options (unsigned int,char const**,unsigned int) ; 
 int /*<<< orphan*/  inform (char*) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  no_unit_at_a_time_default ; 
 int optimize ; 
 int optimize_size ; 
 int read_integral_parameter (char const*,char const*,int) ; 
 int /*<<< orphan*/  set_param_value (char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 unsigned int stub1 (unsigned int,char const**) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_flags ; 
 TYPE_1__ targetm ; 
 scalar_t__ warn_inline ; 
 int warn_uninitialized ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
decode_options (unsigned int argc, const char **argv)
{
  unsigned int i, lang_mask;

  /* Perform language-specific options initialization.  */
  lang_mask = lang_hooks.init_options (argc, argv);

  lang_hooks.initialize_diagnostics (global_dc);

  /* Scan to see what optimization level has been specified.  That will
     determine the default value of many flags.  */
  for (i = 1; i < argc; i++)
    {
      if (!strcmp (argv[i], "-O"))
	{
	  optimize = 1;
	  optimize_size = 0;
	}
      else if (argv[i][0] == '-' && argv[i][1] == 'O')
	{
	  /* Handle -Os, -O2, -O3, -O69, ...  */
	  const char *p = &argv[i][2];

	  if ((p[0] == 's') && (p[1] == 0))
	    {
	      optimize_size = 1;

	      /* Optimizing for size forces optimize to be 2.  */
	      optimize = 2;
	    }
	  else
	    {
	      const int optimize_val = read_integral_parameter (p, p - 2, -1);
	      if (optimize_val != -1)
		{
		  optimize = optimize_val;
		  optimize_size = 0;
		}
	    }
	}
    }

  if (!optimize)
    {
      flag_merge_constants = 0;
    }

  if (optimize >= 1)
    {
      flag_defer_pop = 1;
#ifdef DELAY_SLOTS
      flag_delayed_branch = 1;
#endif
#ifdef CAN_DEBUG_WITHOUT_FP
      flag_omit_frame_pointer = 1;
#endif
      flag_guess_branch_prob = 1;
      flag_cprop_registers = 1;
      flag_if_conversion = 1;
      flag_if_conversion2 = 1;
      flag_ipa_pure_const = 1;
      flag_ipa_reference = 1;
      flag_tree_ccp = 1;
      flag_tree_dce = 1;
      flag_tree_dom = 1;
      flag_tree_dse = 1;
      flag_tree_ter = 1;
      flag_tree_live_range_split = 1;
      flag_tree_sra = 1;
      flag_tree_copyrename = 1;
      flag_tree_fre = 1;
      flag_tree_copy_prop = 1;
      flag_tree_sink = 1;
      flag_tree_salias = 1;
      if (!no_unit_at_a_time_default)
        flag_unit_at_a_time = 1;

      if (!optimize_size)
	{
	  /* Loop header copying usually increases size of the code.  This used
	     not to be true, since quite often it is possible to verify that
	     the condition is satisfied in the first iteration and therefore
	     to eliminate it.  Jump threading handles these cases now.  */
	  flag_tree_ch = 1;
	}
    }

  if (optimize >= 2)
    {
      flag_thread_jumps = 1;
      flag_crossjumping = 1;
      flag_optimize_sibling_calls = 1;
      flag_cse_follow_jumps = 1;
      flag_cse_skip_blocks = 1;
      flag_gcse = 1;
      flag_expensive_optimizations = 1;
      flag_ipa_type_escape = 1;
      flag_rerun_cse_after_loop = 1;
      flag_caller_saves = 1;
      flag_peephole2 = 1;
#ifdef INSN_SCHEDULING
      flag_schedule_insns = 1;
      flag_schedule_insns_after_reload = 1;
#endif
      flag_regmove = 1;
      flag_strict_aliasing = 1;
      flag_strict_overflow = 1;
      flag_delete_null_pointer_checks = 1;
      flag_reorder_blocks = 1;
      flag_reorder_functions = 1;
      flag_tree_store_ccp = 1;
      flag_tree_store_copy_prop = 1;
      /* XXX: some issues with ports have been traced to -ftree-vrp.
         So remove it from -O2 and above.  Note that jdk1{5,6} are affected
         and they build with w/-O3 - so we cannot just move it to -O3. */
      /* flag_tree_vrp = 1; // See GCC tree-optimization/33099 */

      if (!optimize_size)
	{
          /* PRE tends to generate bigger code.  */
          flag_tree_pre = 1;
	}
    }

  if (optimize >= 3)
    {
      flag_inline_functions = 1;
      flag_unswitch_loops = 1;
      flag_gcse_after_reload = 1;
    }

  if (optimize_size)
    {
      align_loops = 1;
      align_jumps = 1;
      align_labels = 1;
      align_functions = 1;

      /* Don't reorder blocks when optimizing for size because extra
	 jump insns may be created; also barrier may create extra padding.

	 More correctly we should have a block reordering mode that tried
	 to minimize the combined size of all the jumps.  This would more
	 or less automatically remove extra jumps, but would also try to
	 use more short jumps instead of long jumps.  */
      flag_reorder_blocks = 0;
      flag_reorder_blocks_and_partition = 0;
    }

  if (optimize_size)
    {
      /* Inlining of very small functions usually reduces total size.  */
      set_param_value ("max-inline-insns-single", 5);
      set_param_value ("max-inline-insns-auto", 5);
      flag_inline_functions = 1;

      /* We want to crossjump as much as possible.  */
      set_param_value ("min-crossjump-insns", 1);
    }

  /* Initialize whether `char' is signed.  */
  flag_signed_char = DEFAULT_SIGNED_CHAR;
  /* Set this to a special "uninitialized" value.  The actual default is set
     after target options have been processed.  */
  flag_short_enums = 2;

  /* Initialize target_flags before OPTIMIZATION_OPTIONS so the latter can
     modify it.  */
  target_flags = targetm.default_target_flags;

  /* Some tagets have ABI-specified unwind tables.  */
  flag_unwind_tables = targetm.unwind_tables_default;

#ifdef OPTIMIZATION_OPTIONS
  /* Allow default optimizations to be specified on a per-machine basis.  */
  OPTIMIZATION_OPTIONS (optimize, optimize_size);
#endif

  handle_options (argc, argv, lang_mask);

  if (flag_pie)
    flag_pic = flag_pie;
  if (flag_pic && !flag_pie)
    flag_shlib = 1;

  if (flag_no_inline == 2)
    flag_no_inline = 0;
  else
    flag_really_no_inline = flag_no_inline;

  /* Set flag_no_inline before the post_options () hook.  The C front
     ends use it to determine tree inlining defaults.  FIXME: such
     code should be lang-independent when all front ends use tree
     inlining, in which case it, and this condition, should be moved
     to the top of process_options() instead.  */
  if (optimize == 0)
    {
      /* Inlining does not work if not optimizing,
	 so force it not to be done.  */
      flag_no_inline = 1;
      warn_inline = 0;

      /* The c_decode_option function and decode_option hook set
	 this to `2' if -Wall is used, so we can avoid giving out
	 lots of errors for people who don't realize what -Wall does.  */
      if (warn_uninitialized == 1)
	warning (OPT_Wuninitialized,
		 "-Wuninitialized is not supported without -O");
    }

  if (flag_really_no_inline == 2)
    flag_really_no_inline = flag_no_inline;

  /* The optimization to partition hot and cold basic blocks into separate
     sections of the .o and executable files does not work (currently)
     with exception handling.  This is because there is no support for
     generating unwind info.  If flag_exceptions is turned on we need to
     turn off the partitioning optimization.  */

  if (flag_exceptions && flag_reorder_blocks_and_partition)
    {
      inform 
	    ("-freorder-blocks-and-partition does not work with exceptions");
      flag_reorder_blocks_and_partition = 0;
      flag_reorder_blocks = 1;
    }

  /* If user requested unwind info, then turn off the partitioning
     optimization.  */

  if (flag_unwind_tables && ! targetm.unwind_tables_default
      && flag_reorder_blocks_and_partition)
    {
      inform ("-freorder-blocks-and-partition does not support unwind info");
      flag_reorder_blocks_and_partition = 0;
      flag_reorder_blocks = 1;
    }

  /* If the target requested unwind info, then turn off the partitioning
     optimization with a different message.  Likewise, if the target does not
     support named sections.  */

  if (flag_reorder_blocks_and_partition
      && (!targetm.have_named_sections
	  || (flag_unwind_tables && targetm.unwind_tables_default)))
    {
      inform 
       ("-freorder-blocks-and-partition does not work on this architecture");
      flag_reorder_blocks_and_partition = 0;
      flag_reorder_blocks = 1;
    }
}
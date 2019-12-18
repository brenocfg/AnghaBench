#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  expand_function; } ;
struct TYPE_15__ {TYPE_1__ callgraph; int /*<<< orphan*/  (* post_options ) (scalar_t__*) ;} ;
struct TYPE_14__ {int (* default_short_enums ) () ;int /*<<< orphan*/  have_named_sections; } ;
struct TYPE_13__ {scalar_t__ var_location; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCUMULATE_OUTGOING_ARGS ; 
 int AUTODETECT_VALUE ; 
 scalar_t__ DBX_DEBUG ; 
 scalar_t__ DINFO_LEVEL_NONE ; 
 scalar_t__ DINFO_LEVEL_NORMAL ; 
 scalar_t__ DWARF2_DEBUG ; 
 int /*<<< orphan*/  FRAME_GROWS_DOWNWARD ; 
 int /*<<< orphan*/  HAVE_prefetch ; 
 int /*<<< orphan*/  MAX_LINE ; 
 scalar_t__ NO_DEBUG ; 
 int /*<<< orphan*/  OPT_fsection_anchors ; 
 int /*<<< orphan*/  OVERRIDE_OPTIONS ; 
 scalar_t__ PREFERRED_DEBUGGING_TYPE ; 
 scalar_t__ SDB_DEBUG ; 
 char* USER_LABEL_PREFIX ; 
 scalar_t__ VMS_AND_DWARF2_DEBUG ; 
 scalar_t__ VMS_DEBUG ; 
 scalar_t__ XCOFF_DEBUG ; 
 int align_functions ; 
 void* align_functions_log ; 
 int align_jumps ; 
 void* align_jumps_log ; 
 int align_jumps_max_skip ; 
 int align_labels ; 
 void* align_labels_log ; 
 int align_labels_max_skip ; 
 int align_loops ; 
 void* align_loops_log ; 
 int align_loops_max_skip ; 
 char* aux_base_name ; 
 scalar_t__ aux_info_file ; 
 int /*<<< orphan*/  aux_info_file_name ; 
 TYPE_2__ dbx_debug_hooks ; 
 TYPE_2__* debug_hooks ; 
 scalar_t__ debug_info_level ; 
 int /*<<< orphan*/ * debug_type_names ; 
 TYPE_2__* default_debug_hooks ; 
 TYPE_2__ do_nothing_debug_hooks ; 
 TYPE_2__ dwarf2_debug_hooks ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (char*,int /*<<< orphan*/ ) ; 
 int flag_asynchronous_unwind_tables ; 
 scalar_t__ flag_complex_method ; 
 scalar_t__ flag_cx_limited_range ; 
 scalar_t__ flag_data_sections ; 
 scalar_t__ flag_delayed_branch ; 
 scalar_t__ flag_function_sections ; 
 scalar_t__ flag_gen_aux_info ; 
 int flag_leading_underscore ; 
 scalar_t__ flag_non_call_exceptions ; 
 scalar_t__ flag_omit_frame_pointer ; 
 scalar_t__ flag_peel_loops ; 
 scalar_t__ flag_prefetch_loop_arrays ; 
 int flag_profile_values ; 
 int flag_rename_registers ; 
 int flag_rerun_cse_after_loop ; 
 scalar_t__ flag_schedule_insns ; 
 scalar_t__ flag_schedule_insns_after_reload ; 
 scalar_t__ flag_section_anchors ; 
 int flag_short_enums ; 
 scalar_t__ flag_signaling_nans ; 
 scalar_t__ flag_stack_protect ; 
 scalar_t__ flag_syntax_only ; 
 int flag_trapping_math ; 
 scalar_t__ flag_unit_at_a_time ; 
 scalar_t__ flag_unroll_all_loops ; 
 int flag_unroll_loops ; 
 int flag_unwind_tables ; 
 scalar_t__ flag_value_profile_transformations ; 
 int flag_var_tracking ; 
 int flag_web ; 
 void* floor_log2 (int) ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ input_filename ; 
 TYPE_6__ lang_hooks ; 
 int /*<<< orphan*/  lbasename (scalar_t__) ; 
 scalar_t__ main_input_filename ; 
 int /*<<< orphan*/  no_backend ; 
 int optimize ; 
 scalar_t__ optimize_size ; 
 int /*<<< orphan*/  print_switch_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ profile_flag ; 
 int /*<<< orphan*/  quiet_flag ; 
 TYPE_2__ sdb_debug_hooks ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strip_off_ending (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*) ; 
 int stub2 () ; 
 int /*<<< orphan*/  target_supports_section_anchors_p () ; 
 TYPE_4__ targetm ; 
 char* user_label_prefix ; 
 scalar_t__ version_flag ; 
 TYPE_2__ vmsdbg_debug_hooks ; 
 scalar_t__ warn_stack_protect ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ write_symbols ; 
 TYPE_2__ xcoff_debug_hooks ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_options (void)
{
  /* Just in case lang_hooks.post_options ends up calling a debug_hook.
     This can happen with incorrect pre-processed input. */
  debug_hooks = &do_nothing_debug_hooks;

  /* Allow the front end to perform consistency checks and do further
     initialization based on the command line options.  This hook also
     sets the original filename if appropriate (e.g. foo.i -> foo.c)
     so we can correctly initialize debug output.  */
  no_backend = lang_hooks.post_options (&main_input_filename);
#ifndef USE_MAPPED_LOCATION
  input_filename = main_input_filename;
#endif

#ifdef OVERRIDE_OPTIONS
  /* Some machines may reject certain combinations of options.  */
  OVERRIDE_OPTIONS;
#endif

  if (flag_section_anchors && !target_supports_section_anchors_p ())
    {
      warning (OPT_fsection_anchors,
	       "this target does not support %qs", "-fsection-anchors");
      flag_section_anchors = 0;
    }

  if (flag_short_enums == 2)
    flag_short_enums = targetm.default_short_enums ();

  /* Set aux_base_name if not already set.  */
  if (aux_base_name)
    ;
  else if (main_input_filename)
    {
      char *name = xstrdup (lbasename (main_input_filename));

      strip_off_ending (name, strlen (name));
      aux_base_name = name;
    }
  else
    aux_base_name = "gccaux";

  /* Set up the align_*_log variables, defaulting them to 1 if they
     were still unset.  */
  if (align_loops <= 0) align_loops = 1;
  if (align_loops_max_skip > align_loops || !align_loops)
    align_loops_max_skip = align_loops - 1;
  align_loops_log = floor_log2 (align_loops * 2 - 1);
  if (align_jumps <= 0) align_jumps = 1;
  if (align_jumps_max_skip > align_jumps || !align_jumps)
    align_jumps_max_skip = align_jumps - 1;
  align_jumps_log = floor_log2 (align_jumps * 2 - 1);
  if (align_labels <= 0) align_labels = 1;
  align_labels_log = floor_log2 (align_labels * 2 - 1);
  if (align_labels_max_skip > align_labels || !align_labels)
    align_labels_max_skip = align_labels - 1;
  if (align_functions <= 0) align_functions = 1;
  align_functions_log = floor_log2 (align_functions * 2 - 1);

  /* Unrolling all loops implies that standard loop unrolling must also
     be done.  */
  if (flag_unroll_all_loops)
    flag_unroll_loops = 1;

  /* The loop unrolling code assumes that cse will be run after loop.
     web and rename-registers also help when run after loop unrolling.  */

  if (flag_rerun_cse_after_loop == AUTODETECT_VALUE)
    flag_rerun_cse_after_loop = flag_unroll_loops || flag_peel_loops;
  if (flag_web == AUTODETECT_VALUE)
    flag_web = flag_unroll_loops || flag_peel_loops;
  if (flag_rename_registers == AUTODETECT_VALUE)
    flag_rename_registers = flag_unroll_loops || flag_peel_loops;

  if (flag_non_call_exceptions)
    flag_asynchronous_unwind_tables = 1;
  if (flag_asynchronous_unwind_tables)
    flag_unwind_tables = 1;

  /* Disable unit-at-a-time mode for frontends not supporting callgraph
     interface.  */
  if (flag_unit_at_a_time && ! lang_hooks.callgraph.expand_function)
    flag_unit_at_a_time = 0;

  if (!flag_unit_at_a_time)
    flag_section_anchors = 0;

  if (flag_value_profile_transformations)
    flag_profile_values = 1;

  /* Warn about options that are not supported on this machine.  */
#ifndef INSN_SCHEDULING
  if (flag_schedule_insns || flag_schedule_insns_after_reload)
    warning (0, "instruction scheduling not supported on this target machine");
#endif
#ifndef DELAY_SLOTS
  if (flag_delayed_branch)
    warning (0, "this target machine does not have delayed branches");
#endif

  user_label_prefix = USER_LABEL_PREFIX;
  if (flag_leading_underscore != -1)
    {
      /* If the default prefix is more complicated than "" or "_",
	 issue a warning and ignore this option.  */
      if (user_label_prefix[0] == 0 ||
	  (user_label_prefix[0] == '_' && user_label_prefix[1] == 0))
	{
	  user_label_prefix = flag_leading_underscore ? "_" : "";
	}
      else
	warning (0, "-f%sleading-underscore not supported on this target machine",
		 flag_leading_underscore ? "" : "no-");
    }

  /* If we are in verbose mode, write out the version and maybe all the
     option flags in use.  */
  if (version_flag)
    {
      print_version (stderr, "");
      if (! quiet_flag)
	print_switch_values (stderr, 0, MAX_LINE, "", " ", "\n");
    }

  if (flag_syntax_only)
    {
      write_symbols = NO_DEBUG;
      profile_flag = 0;
    }

  /* A lot of code assumes write_symbols == NO_DEBUG if the debugging
     level is 0.  */
  if (debug_info_level == DINFO_LEVEL_NONE)
    write_symbols = NO_DEBUG;

  /* Now we know write_symbols, set up the debug hooks based on it.
     By default we do nothing for debug output.  */
  if (PREFERRED_DEBUGGING_TYPE == NO_DEBUG)
    default_debug_hooks = &do_nothing_debug_hooks;
#if defined(DBX_DEBUGGING_INFO)
  else if (PREFERRED_DEBUGGING_TYPE == DBX_DEBUG)
    default_debug_hooks = &dbx_debug_hooks;
#endif
#if defined(XCOFF_DEBUGGING_INFO)
  else if (PREFERRED_DEBUGGING_TYPE == XCOFF_DEBUG)
    default_debug_hooks = &xcoff_debug_hooks;
#endif
#ifdef SDB_DEBUGGING_INFO
  else if (PREFERRED_DEBUGGING_TYPE == SDB_DEBUG)
    default_debug_hooks = &sdb_debug_hooks;
#endif
#ifdef DWARF2_DEBUGGING_INFO
  else if (PREFERRED_DEBUGGING_TYPE == DWARF2_DEBUG)
    default_debug_hooks = &dwarf2_debug_hooks;
#endif
#ifdef VMS_DEBUGGING_INFO
  else if (PREFERRED_DEBUGGING_TYPE == VMS_DEBUG
	   || PREFERRED_DEBUGGING_TYPE == VMS_AND_DWARF2_DEBUG)
    default_debug_hooks = &vmsdbg_debug_hooks;
#endif

  if (write_symbols == NO_DEBUG)
    ;
#if defined(DBX_DEBUGGING_INFO)
  else if (write_symbols == DBX_DEBUG)
    debug_hooks = &dbx_debug_hooks;
#endif
#if defined(XCOFF_DEBUGGING_INFO)
  else if (write_symbols == XCOFF_DEBUG)
    debug_hooks = &xcoff_debug_hooks;
#endif
#ifdef SDB_DEBUGGING_INFO
  else if (write_symbols == SDB_DEBUG)
    debug_hooks = &sdb_debug_hooks;
#endif
#ifdef DWARF2_DEBUGGING_INFO
  else if (write_symbols == DWARF2_DEBUG)
    debug_hooks = &dwarf2_debug_hooks;
#endif
#ifdef VMS_DEBUGGING_INFO
  else if (write_symbols == VMS_DEBUG || write_symbols == VMS_AND_DWARF2_DEBUG)
    debug_hooks = &vmsdbg_debug_hooks;
#endif
  else
    error ("target system does not support the \"%s\" debug format",
	   debug_type_names[write_symbols]);

  /* Now we know which debug output will be used so we can set
     flag_var_tracking, flag_rename_registers if the user has
     not specified them.  */
  if (debug_info_level < DINFO_LEVEL_NORMAL
      || debug_hooks->var_location == do_nothing_debug_hooks.var_location)
    {
      if (flag_var_tracking == 1)
        {
	  if (debug_info_level < DINFO_LEVEL_NORMAL)
	    warning (0, "variable tracking requested, but useless unless "
		     "producing debug info");
	  else
	    warning (0, "variable tracking requested, but not supported "
		     "by this debug format");
	}
      flag_var_tracking = 0;
    }

  if (flag_rename_registers == AUTODETECT_VALUE)
    flag_rename_registers = default_debug_hooks->var_location
	    		    != do_nothing_debug_hooks.var_location;

  if (flag_var_tracking == AUTODETECT_VALUE)
    flag_var_tracking = optimize >= 1;

  /* If auxiliary info generation is desired, open the output file.
     This goes in the same directory as the source file--unlike
     all the other output files.  */
  if (flag_gen_aux_info)
    {
      aux_info_file = fopen (aux_info_file_name, "w");
      if (aux_info_file == 0)
	fatal_error ("can%'t open %s: %m", aux_info_file_name);
    }

  if (! targetm.have_named_sections)
    {
      if (flag_function_sections)
	{
	  warning (0, "-ffunction-sections not supported for this target");
	  flag_function_sections = 0;
	}
      if (flag_data_sections)
	{
	  warning (0, "-fdata-sections not supported for this target");
	  flag_data_sections = 0;
	}
    }

  if (flag_function_sections && profile_flag)
    {
      warning (0, "-ffunction-sections disabled; it makes profiling impossible");
      flag_function_sections = 0;
    }

#ifndef HAVE_prefetch
  if (flag_prefetch_loop_arrays)
    {
      warning (0, "-fprefetch-loop-arrays not supported for this target");
      flag_prefetch_loop_arrays = 0;
    }
#else
  if (flag_prefetch_loop_arrays && !HAVE_prefetch)
    {
      warning (0, "-fprefetch-loop-arrays not supported for this target (try -march switches)");
      flag_prefetch_loop_arrays = 0;
    }
#endif

  /* This combination of options isn't handled for i386 targets and doesn't
     make much sense anyway, so don't allow it.  */
  if (flag_prefetch_loop_arrays && optimize_size)
    {
      warning (0, "-fprefetch-loop-arrays is not supported with -Os");
      flag_prefetch_loop_arrays = 0;
    }

#ifndef OBJECT_FORMAT_ELF
#ifndef OBJECT_FORMAT_MACHO
  if (flag_function_sections && write_symbols != NO_DEBUG)
    warning (0, "-ffunction-sections may affect debugging on some targets");
#endif
#endif

  /* The presence of IEEE signaling NaNs, implies all math can trap.  */
  if (flag_signaling_nans)
    flag_trapping_math = 1;

  /* With -fcx-limited-range, we do cheap and quick complex arithmetic.  */
  if (flag_cx_limited_range)
    flag_complex_method = 0;

  /* Targets must be able to place spill slots at lower addresses.  If the
     target already uses a soft frame pointer, the transition is trivial.  */
  if (!FRAME_GROWS_DOWNWARD && flag_stack_protect)
    {
      warning (0, "-fstack-protector not supported for this target");
      flag_stack_protect = 0;
    }
  if (!flag_stack_protect)
    warn_stack_protect = 0;

  /* ??? Unwind info is not correct around the CFG unless either a frame
     pointer is present or A_O_A is set.  Fixing this requires rewriting
     unwind info generation to be aware of the CFG and propagating states
     around edges.  */
  if (flag_unwind_tables && !ACCUMULATE_OUTGOING_ARGS
      && flag_omit_frame_pointer)
    {
      warning (0, "unwind tables currently requires a frame pointer "
	       "for correctness");
      flag_omit_frame_pointer = 0;
    }
}
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
 scalar_t__ DINFO_LEVEL_NONE ; 
 scalar_t__ DINFO_LEVEL_NORMAL ; 
 scalar_t__ DINFO_LEVEL_VERBOSE ; 
 scalar_t__ debug_info_level ; 
 int /*<<< orphan*/  expand_dummy_function_end () ; 
 scalar_t__ flag_caller_saves ; 
 scalar_t__ flag_test_coverage ; 
 int /*<<< orphan*/  init_alias_once () ; 
 int /*<<< orphan*/  init_caller_save () ; 
 int /*<<< orphan*/  init_dummy_function_start () ; 
 int /*<<< orphan*/  init_emit_once (int) ; 
 int /*<<< orphan*/  init_expmed () ; 
 int /*<<< orphan*/  init_fake_stack_mems () ; 
 int /*<<< orphan*/  init_regs () ; 
 int /*<<< orphan*/  init_reload () ; 
 int /*<<< orphan*/  init_rtlanal () ; 
 int /*<<< orphan*/  init_varasm_once () ; 

__attribute__((used)) static void
backend_init (void)
{
  init_emit_once (debug_info_level == DINFO_LEVEL_NORMAL
		  || debug_info_level == DINFO_LEVEL_VERBOSE
#ifdef VMS_DEBUGGING_INFO
		    /* Enable line number info for traceback.  */
		    || debug_info_level > DINFO_LEVEL_NONE
#endif
		    || flag_test_coverage);

  init_rtlanal ();
  init_regs ();
  init_fake_stack_mems ();
  init_alias_once ();
  init_reload ();
  init_varasm_once ();

  /* The following initialization functions need to generate rtl, so
     provide a dummy function context for them.  */
  init_dummy_function_start ();
  init_expmed ();
  if (flag_caller_saves)
    init_caller_save ();
  expand_dummy_function_end ();
}